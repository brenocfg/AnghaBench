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
typedef  double real ;
typedef  int /*<<< orphan*/  CREC ;

/* Variables and functions */
 int MAX_STRING_LENGTH ; 
 long long array_size ; 
 scalar_t__ atof (char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 long long atoll (char*) ; 
 int /*<<< orphan*/  file_head ; 
 int find_arg (char*,int,char**) ; 
 int /*<<< orphan*/  malloc (int) ; 
 scalar_t__ memory_limit ; 
 int /*<<< orphan*/  printf (char*) ; 
 int shuffle_by_chunks () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  verbose ; 

int main(int argc, char **argv) {
    int i;
    file_head = malloc(sizeof(char) * MAX_STRING_LENGTH);
    
    if (argc == 1) {
        printf("Tool to shuffle entries of word-word cooccurrence files\n");
        printf("Author: Jeffrey Pennington (jpennin@stanford.edu)\n\n");
        printf("Usage options:\n");
        printf("\t-verbose <int>\n");
        printf("\t\tSet verbosity: 0, 1, or 2 (default)\n");
        printf("\t-memory <float>\n");
        printf("\t\tSoft limit for memory consumption, in GB; default 4.0\n");
        printf("\t-array-size <int>\n");
        printf("\t\tLimit to length <int> the buffer which stores chunks of data to shuffle before writing to disk. \n\t\tThis value overrides that which is automatically produced by '-memory'.\n");
        printf("\t-temp-file <file>\n");
        printf("\t\tFilename, excluding extension, for temporary files; default temp_shuffle\n");
        
        printf("\nExample usage: (assuming 'cooccurrence.bin' has been produced by 'coccur')\n");
        printf("./shuffle -verbose 2 -memory 8.0 < cooccurrence.bin > cooccurrence.shuf.bin\n");
        return 0;
    }
   
    if ((i = find_arg((char *)"-verbose", argc, argv)) > 0) verbose = atoi(argv[i + 1]);
    if ((i = find_arg((char *)"-temp-file", argc, argv)) > 0) strcpy(file_head, argv[i + 1]);
    else strcpy(file_head, (char *)"temp_shuffle");
    if ((i = find_arg((char *)"-memory", argc, argv)) > 0) memory_limit = atof(argv[i + 1]);
    array_size = (long long) (0.95 * (real)memory_limit * 1073741824/(sizeof(CREC)));
    if ((i = find_arg((char *)"-array-size", argc, argv)) > 0) array_size = atoll(argv[i + 1]);
    return shuffle_by_chunks();
}