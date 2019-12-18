#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 void* atoll (char*) ; 
 int find_arg (char*,int,char**) ; 
 int get_counts () ; 
 void* max_vocab ; 
 void* min_count ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  verbose ; 

int main(int argc, char **argv) {
    int i;
    if (argc == 1) {
        printf("Simple tool to extract unigram counts\n");
        printf("Author: Jeffrey Pennington (jpennin@stanford.edu)\n\n");
        printf("Usage options:\n");
        printf("\t-verbose <int>\n");
        printf("\t\tSet verbosity: 0, 1, or 2 (default)\n");
        printf("\t-max-vocab <int>\n");
        printf("\t\tUpper bound on vocabulary size, i.e. keep the <int> most frequent words. The minimum frequency words are randomly sampled so as to obtain an even distribution over the alphabet.\n");
        printf("\t-min-count <int>\n");
        printf("\t\tLower limit such that words which occur fewer than <int> times are discarded.\n");
        printf("\nExample usage:\n");
        printf("./vocab_count -verbose 2 -max-vocab 100000 -min-count 10 < corpus.txt > vocab.txt\n");
        return 0;
    }
    
    if ((i = find_arg((char *)"-verbose", argc, argv)) > 0) verbose = atoi(argv[i + 1]);
    if ((i = find_arg((char *)"-max-vocab", argc, argv)) > 0) max_vocab = atoll(argv[i + 1]);
    if ((i = find_arg((char *)"-min-count", argc, argv)) > 0) min_count = atoll(argv[i + 1]);
    return get_counts();
}