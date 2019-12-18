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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CREC ;

/* Variables and functions */
 int MAX_STRING_LENGTH ; 
 int array_size ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 char* file_head ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  shuffle (int /*<<< orphan*/ *,long) ; 
 int shuffle_merge (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int verbose ; 
 int /*<<< orphan*/  write_chunk (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *) ; 

int shuffle_by_chunks() {
    long i = 0, l = 0;
    int fidcounter = 0;
    char filename[MAX_STRING_LENGTH];
    CREC *array;
    FILE *fin = stdin, *fid;
    array = malloc(sizeof(CREC) * array_size);
    
    fprintf(stderr,"SHUFFLING COOCCURRENCES\n");
    if (verbose > 0) fprintf(stderr,"array size: %lld\n", array_size);
    sprintf(filename,"%s_%04d.bin",file_head, fidcounter);
    fid = fopen(filename,"w");
    if (fid == NULL) {
        fprintf(stderr, "Unable to open file %s.\n",filename);
        return 1;
    }
    if (verbose > 1) fprintf(stderr, "Shuffling by chunks: processed 0 lines.");
    
    while (1) { //Continue until EOF
        if (i >= array_size) {// If array is full, shuffle it and save to temporary file
            shuffle(array, i-2);
            l += i;
            if (verbose > 1) fprintf(stderr, "\033[22Gprocessed %ld lines.", l);
            write_chunk(array,i,fid);
            fclose(fid);
            fidcounter++;
            sprintf(filename,"%s_%04d.bin",file_head, fidcounter);
            fid = fopen(filename,"w");
            if (fid == NULL) {
                fprintf(stderr, "Unable to open file %s.\n",filename);
                return 1;
            }
            i = 0;
        }
        fread(&array[i], sizeof(CREC), 1, fin);
        if (feof(fin)) break;
        i++;
    }
    shuffle(array, i-2); //Last chunk may be smaller than array_size
    write_chunk(array,i,fid);
    l += i;
    if (verbose > 1) fprintf(stderr, "\033[22Gprocessed %ld lines.\n", l);
    if (verbose > 1) fprintf(stderr, "Wrote %d temporary file(s).\n", fidcounter + 1);
    fclose(fid);
    free(array);
    return shuffle_merge(fidcounter + 1); // Merge and shuffle together temporary files
}