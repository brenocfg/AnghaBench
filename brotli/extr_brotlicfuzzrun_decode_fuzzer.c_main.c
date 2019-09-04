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

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  LLVMFuzzerTestOneInput (unsigned char*,size_t) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t fread (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char* *argv) {
  if (argc != 2) {
    fprintf(stderr, "Exactly one argument is expected.\n");
    exit(EXIT_FAILURE);
  }

  FILE* f = fopen(argv[1], "r");
  if (!f) {
    fprintf(stderr, "Failed to open input file.");
    exit(EXIT_FAILURE);
  }

  size_t max_len = 1 << 20;
  unsigned char* tmp = (unsigned char*)malloc(max_len);
  size_t len = fread(tmp, 1, max_len, f);
  if (ferror(f)) {
    fclose(f);
    fprintf(stderr, "Failed read input file.");
    exit(EXIT_FAILURE);
  }
  /* Make data after the end "inaccessible". */
  unsigned char* data = (unsigned char*)malloc(len);
  memcpy(data, tmp, len);
  free(tmp);

  LLVMFuzzerTestOneInput(data, len);
  free(data);
  exit(EXIT_SUCCESS);
}