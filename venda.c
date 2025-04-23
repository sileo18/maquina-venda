#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#ifdef WINDOWS
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct 
{
    char nome[20];
    int quantidade;
    float preco;    
}Produto ;

void inserirSaldo(float* saldo) {

    float notas[] = {2.0f, 5.0f, 10.0f, 20.0f, 50.0f, 100.0f};
    int qtdNotas = sizeof(notas) / sizeof(float);

    for(int i = 0; i < qtdNotas; i++) {
        printf("%d. R$ %.2f\n", i + 1, notas[i]);
    };

    printf("Escolha uma das notas acima para inserir: (Caso já tenha inserido, digite 0 para continuar)\n");
    int escolha;

    scanf("%d", &escolha);

    if(escolha == 0) {
        return;
    } else if (escolha >= 1 && escolha <= qtdNotas) {
        *saldo += notas[escolha - 1];
        return;
    } else {
        printf("Opção inválida!\n");
    }
}

void exibirProdutos(Produto *maquina[], float saldo, int tamanho) {

    system(CLEAR);
    printf("===== MÁQUINA DE VENDAS =====\n\n");

    for(int i = 0; i< tamanho; i++) {
        printf("%d. %s - R$%.2f (Em estoque: %d)\n", i + 1, maquina[i]->nome, maquina[i]->preco, maquina[i]->quantidade);	
    }

    printf("\nSaldo atual: R$%.2f ", saldo);
    printf("\nEscolha um produto (0 para sair): \n\n");
}

void executarVenda(Produto* produto, float* saldo) {

    if(produto->quantidade <= 0) {
        printf("\n\nProduto esgotado!\n");
        printf("Escolha outro produto.\n\n");
        return;       
    }

    if(*saldo < produto->preco) {
        printf("Saldo insuficiente!\n\n");
        return;
    }

    produto->quantidade--;
    *saldo -= produto->preco;
    printf("\n\nVocê comprou %s por R$%.2f!\n", produto->nome, produto->preco);
    printf("Seu saldo atual é R$%.2f!\n\n", *saldo);
}

int main() {

    setlocale(LC_ALL, "Portuguese");

    Produto itens[] = {
        {"Chocolate", 1, 7.5},
        {"Carne", 50, 35.0},
        {"Suco", 100, 6.0},
        {"Refrigerante", 20, 5.0},
        {"Biscoito", 30, 2.5},
        {"Pipoca", 15, 3.0},
        {"Salgadinho", 25, 4.0},
        {"Água", 50, 1.0},
        {"Cerveja", 10, 8.0},
        {"Energetico", 5, 12.0}
    };

    const int PRODUTO_QTD = sizeof(itens) / sizeof(Produto);

    Produto *maquina[PRODUTO_QTD];    

    for(int i = 0; i < PRODUTO_QTD ; i++) {
        maquina[i] = &itens[i];
    }

    int opcao = -1;

    float saldo = 0.0f;

    while(opcao != 0) {
        system(CLEAR);
        inserirSaldo(&saldo);
        exibirProdutos(maquina, saldo, PRODUTO_QTD);
        scanf("%d", &opcao);
        
        if(opcao > 0 && opcao <= PRODUTO_QTD) {
            executarVenda(maquina[opcao - 1], &saldo);
        }
        
    }

    return 0;

}
