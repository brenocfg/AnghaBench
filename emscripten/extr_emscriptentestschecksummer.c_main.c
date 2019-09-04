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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ adler32 (unsigned char*,long) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 size_t fread (unsigned char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char* argv[]) {
    long bufsize;

    if (argc != 2) {
	fputs("Need 1 argument\n", stderr);
	return (EXIT_FAILURE);
    }

    unsigned char *source = NULL;
    FILE *fp = fopen(argv[1], "rb");
    if (fp != NULL) {
        /* Go to the end of the file. */
        if (fseek(fp, 0L, SEEK_END) == 0) {
            /* Get the size of the file. */
            bufsize = ftell(fp);
            if (bufsize == -1) { fputs("Couldn't get size\n", stderr); return (EXIT_FAILURE); }
    
            /* Allocate our buffer to that size. */
            source = malloc(sizeof(char) * (bufsize + 1));
            if (source == NULL) { fputs("Couldn't allocate\n", stderr); return (EXIT_FAILURE); }
    
            /* Go back to the start of the file. */
            if (fseek(fp, 0L, SEEK_SET) == -1) { fputs("Couldn't seek\n", stderr); return (EXIT_FAILURE); }
    
            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if (newLen == 0) {
                fputs("Error reading file\n", stderr);
                //return (EXIT_FAILURE);
            } else {
                source[++newLen] = '\0'; /* Just to be safe. */
            }
        } else {
          fputs("Couldn't seek to end\n", stderr);
          return (EXIT_FAILURE);
        }
        fclose(fp);
    } else {
      fputs("Couldn't open\n", stderr);
      return (EXIT_FAILURE);
    }

    printf("%u\n", (uint32_t) adler32(source, bufsize));
    
    free(source); /* Don't forget to call free() later! */

    return (EXIT_SUCCESS);

}