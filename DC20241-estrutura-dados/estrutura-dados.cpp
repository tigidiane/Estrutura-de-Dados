/*
TRABALHO DE ESTRUTURA DE DADOS
ALUNA: GIDIANE FARIAS DE OLIVEIRA
TURNO: NOITE / 2024.1

ENUNCIADO:
Um condomínio de apartamentos não possui vagas de garagem para todos os apartamentos. 
São apenas 10 vagas de garagem. Isso faz com que exista uma fila de espera por vagas. 
O apartamento é composto de número do ap, nome do proprietário e número da vaga, quando este tem vaga. 
Quando ele não tem vaga, este número é zero. Implemente uma fila de espera
que contenha os métodos para adicionar apartamentos na fila, retirar apartamentos 
informando o número da vaga que este apartamento receberá e um método para imprimir a fila de espera.
Implemente uma lista encadeada de apartamentos que possuem vagas de garagem.
Implemente uma função de leberar vaga, informando qual apartamento liberou a vaga. 
Então o primeiro apartamento da fila de espera, deve sair da fila e assumir o lugar 
do apartamento que liberou a vaga, na lista encadeada. Este apartamento que liberou a vaga, 
deve ir para o fim da fila de espera. 
Alem da entrega do código, este trabalho deve ser apresentado.
A entrega deve ser via GitHub, envie aqui apenas o link do GitHub contendo o código desenvolvido.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaração da variável global para controlar o número de vagas ocupadas
int numero_vagas_ocupadas = 0;

// Estrutura para representar um apartamento e a fila de espera por vagas de garagem
typedef struct Apartamento {
    int numero;
    char proprietario[100];
    int numero_vaga;
    struct Apartamento* proximo;
} Apartamento;

// Função para inicializar a fila de espera por vagas de garagem
void inicializar_fila(Apartamento **fila) {
    *fila = NULL;
}

// Função para adicionar apartamento na lista de disponíveis ou na fila de espera por vagas
void adicionar_apartamento(Apartamento **lista, int numero_apartamento, const char* proprietario, int numero_vaga) {
    if (numero_vagas_ocupadas >= 10) {
        printf("Não há mais vagas de garagem. Adicionando o apartamento à fila de espera.\n");
        numero_vaga = 0; // Define o número da vaga como 0, indicando que está na fila de espera
    } else {
        numero_vagas_ocupadas++; // Incrementa o número de vagas ocupadas
    }

    Apartamento* novo_apartamento = (Apartamento*) malloc(sizeof(Apartamento));
    if (novo_apartamento == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    novo_apartamento->numero = numero_apartamento;
    strcpy(novo_apartamento->proprietario, proprietario);
    novo_apartamento->numero_vaga = numero_vaga;
    novo_apartamento->proximo = *lista;
    *lista = novo_apartamento;
}

// Função para remover o primeiro apartamento disponível da lista encadeada
int remover_apartamento(Apartamento** lista) {
    if (*lista == NULL) {
        return -1; // Retorna -1 se não houver apartamentos disponíveis
    }

    Apartamento* removido = *lista;
    int numero_apartamento = removido->numero;

    *lista = removido->proximo;
    free(removido);

    return numero_apartamento;
}

// Função para imprimir a lista de apartamentos disponíveis
void imprimir_apartamentos(Apartamento* lista) {
    if (lista == NULL) {
        printf("Nao ha apartamentos disponiveis no momento.\n");
        return;
    }

    printf("Lista de apartamentos disponiveis:\n");
    while (lista != NULL) {
        printf("Apartamento: %d\n", lista->numero);
        printf("Proprietario: %s\n", lista->proprietario);
        printf("Numero da vaga: %d\n", lista->numero_vaga);
        printf("\n");
        lista = lista->proximo;
    }
}

// Função para liberar vaga, movendo o primeiro apartamento da fila de espera para a lista encadeada
void liberar_vaga(Apartamento **fila, int numero_apartamento_liberado) {
    if (*fila == NULL) {
        printf("A fila de espera por vagas de garagem esta vazia.\n");
        return;
    }

    // Remover o primeiro apartamento da fila de espera
    int numero_apartamento_espera = remover_apartamento(fila);

    // Adicionar o apartamento que liberou a vaga na lista encadeada
    adicionar_apartamento(fila, numero_apartamento_liberado, "Sem proprietario", 0);

    printf("O apartamento %d liberou a vaga. O apartamento %d assumiu a vaga.\n", (*fila)->numero, numero_apartamento_espera);
}

// Função principal
int main() {

    Apartamento* lista_apartamentos;
    inicializar_fila(&lista_apartamentos);

    int opcao, numero_apartamento, numero_vaga;
    char proprietario[100];

    printf("\nMenu:\n");
    printf("1. Adicionar apartamento na lista de disponiveis\n");
    printf("2. Remover apartamento da lista de disponiveis\n");
    printf("3. Imprimir lista de apartamentos disponiveis\n");
    printf("4. Liberar vaga\n");
    printf("0. Sair\n");

    while (1) {
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o numero do apartamento a ser adicionado: ");
            scanf("%d", &numero_apartamento);
            printf("Digite o nome do proprietario: ");
            scanf("%s", proprietario);
            printf("Digite o numero da vaga: ");
            scanf("%d", &numero_vaga);
            adicionar_apartamento(&lista_apartamentos, numero_apartamento, proprietario, numero_vaga);
        } else if (opcao == 2) {
            numero_apartamento = remover_apartamento(&lista_apartamentos);
            if (numero_apartamento == -1) {
                printf("Nao ha apartamentos disponiveis para remover.\n");
            } else {
                printf("Apartamento %d removido da lista de disponiveis.\n", numero_apartamento);
            }
        } else if (opcao == 3) {
            imprimir_apartamentos(lista_apartamentos);
        } else if (opcao == 4) {
            printf("Digite o numero do apartamento que liberou a vaga: ");
            scanf("%d", &numero_apartamento);
            liberar_vaga(&lista_apartamentos, numero_apartamento);
        } else if (opcao == 0) {
            printf("Encerrando o programa...\n");
            break;
        } else {
            printf("Opcao invalida. Eescolha uma opcao valida.\n");
        }
    }

    return 0;
}