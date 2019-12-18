#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int inputs; int n; TYPE_1__* layers; } ;
typedef  TYPE_2__ network ;
struct TYPE_5__ {float temperature; } ;

/* Variables and functions */
 int EOF ; 
 char* basecfg (char*) ; 
 float* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getc (int /*<<< orphan*/ ) ; 
 TYPE_2__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 float* network_predict (TYPE_2__*,float*) ; 
 int /*<<< orphan*/  print_symbol (int,char**) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char** read_tokens (char*,size_t*) ; 
 int sample_array (float*,int) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

void test_tactic_rnn(char *cfgfile, char *weightfile, int num, float temp, int rseed, char *token_file)
{
    char **tokens = 0;
    if(token_file){
        size_t n;
        tokens = read_tokens(token_file, &n);
    }

    srand(rseed);
    char *base = basecfg(cfgfile);
    fprintf(stderr, "%s\n", base);

    network *net = load_network(cfgfile, weightfile, 0);
    int inputs = net->inputs;

    int i, j;
    for(i = 0; i < net->n; ++i) net->layers[i].temperature = temp;
    int c = 0;
    float *input = calloc(inputs, sizeof(float));
    float *out = 0;

    while((c = getc(stdin)) != EOF){
        input[c] = 1;
        out = network_predict(net, input);
        input[c] = 0;
    }
    for(i = 0; i < num; ++i){
        for(j = 0; j < inputs; ++j){
            if (out[j] < .0001) out[j] = 0;
        }
        int next = sample_array(out, inputs);
        if(c == '.' && next == '\n') break;
        c = next;
        print_symbol(c, tokens);

        input[c] = 1;
        out = network_predict(net, input);
        input[c] = 0;
    }
    printf("\n");
}