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
struct magic_set {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_NONE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  magic_close (struct magic_set*) ; 
 char* magic_error (struct magic_set*) ; 
 char* magic_file (struct magic_set*,char*) ; 
 int magic_load (struct magic_set*,int /*<<< orphan*/ *) ; 
 struct magic_set* magic_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 char* slurp (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
main(int argc, char **argv)
{
	struct magic_set *ms;
	const char *result;
	char *desired;
	size_t desired_len;
	int i;
	FILE *fp;

	ms = magic_open(MAGIC_NONE);
	if (ms == NULL) {
		(void)fprintf(stderr, "ERROR opening MAGIC_NONE: out of memory\n");
		return 10;
	}
	if (magic_load(ms, NULL) == -1) {
		(void)fprintf(stderr, "ERROR loading with NULL file: %s\n",
		    magic_error(ms));
		return 11;
	}

	if (argc > 1) {
		if (argc != 3) {
			(void)fprintf(stderr, "Usage: test TEST-FILE RESULT\n");
		} else {
			if ((result = magic_file(ms, argv[1])) == NULL) {
				(void)fprintf(stderr, "ERROR loading file %s: %s\n", argv[1], magic_error(ms));
				return 12;
			} else {
				fp = fopen(argv[2], "r");
				if (fp == NULL) {
					(void)fprintf(stderr, "ERROR opening `%s': ", argv[2]);
					perror(NULL);
					return 13;
				}
				desired = slurp(fp, &desired_len);
				fclose(fp);
				(void)printf("%s: %s\n", argv[1], result);
                                if (strcmp(result, desired) != 0) {
					(void)fprintf(stderr, "Error: result was\n%s\nexpected:\n%s\n", result, desired);
					return 1;
                                }
			}
		}
	}

	magic_close(ms);
	return 0;
}