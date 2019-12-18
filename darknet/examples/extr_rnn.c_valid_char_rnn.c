#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int inputs; } ;
typedef  TYPE_1__ network ;

/* Variables and functions */
 int EOF ; 
 char* basecfg (char*) ; 
 float* calloc (int,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getc (int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 float log (float) ; 
 float* network_predict (TYPE_1__*,float*) ; 
 double pow (int,float) ; 
 int /*<<< orphan*/  printf (char*,int,float,double,double) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

void valid_char_rnn(char *cfgfile, char *weightfile, char *seed)
{
    char *base = basecfg(cfgfile);
    fprintf(stderr, "%s\n", base);

    network *net = load_network(cfgfile, weightfile, 0);
    int inputs = net->inputs;

    int count = 0;
    int words = 1;
    int c;
    int len = strlen(seed);
    float *input = calloc(inputs, sizeof(float));
    int i;
    for(i = 0; i < len; ++i){
        c = seed[i];
        input[(int)c] = 1;
        network_predict(net, input);
        input[(int)c] = 0;
    }
    float sum = 0;
    c = getc(stdin);
    float log2 = log(2);
    while(c != EOF){
        int next = getc(stdin);
        if(next == EOF) break;
        if(next < 0 || next >= 255) error("Out of range character");
        ++count;
        if(next == ' ' || next == '\n' || next == '\t') ++words;
        input[c] = 1;
        float *out = network_predict(net, input);
        input[c] = 0;
        sum += log(out[next])/log2;
        c = next;
        printf("%d BPC: %4.4f   Perplexity: %4.4f    Word Perplexity: %4.4f\n", count, -sum/count, pow(2, -sum/count), pow(2, -sum/words));
    }
}