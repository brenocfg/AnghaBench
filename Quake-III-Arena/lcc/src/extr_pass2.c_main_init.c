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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int errlimit ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int glevel ; 
 char* rcsid ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  wflag ; 

void main_init(int argc, char *argv[]) {
	int i;
	static int inited;

	if (inited)
		return;
	inited = 1;
	for (i = 1; i < argc; i++)
		if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "-g2") == 0)
			glevel = 2;
		else if (strcmp(argv[i], "-w") == 0)
			wflag++;
		else if (strcmp(argv[i], "-v") == 0) {
			fprint(stderr, "%s %s\n", argv[0], rcsid);
			verbose++;
		} else if (strncmp(argv[i], "-errout=", 8) == 0) {
			FILE *f = fopen(argv[i]+8, "w");
			if (f == NULL) {
				fprint(stderr, "%s: can't write errors to `%s'\n", argv[0], argv[i]+8);
				exit(EXIT_FAILURE);
			}
			fclose(f);
			f = freopen(argv[i]+8, "w", stderr);
			assert(f);
		} else if (strncmp(argv[i], "-e", 2) == 0) {
			int x;
			if ((x = strtol(&argv[i][2], NULL, 0)) > 0)
				errlimit = x;
		}
}