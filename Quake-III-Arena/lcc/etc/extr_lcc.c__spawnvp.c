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
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int wait (int*) ; 

__attribute__((used)) static int _spawnvp(int mode, const char *cmdname, char *argv[]) {
	int pid, n, status;

	switch (pid = fork()) {
	case -1:
		fprintf(stderr, "%s: no more processes\n", progname);
		return 100;
	case 0:
		// TTimo removing hardcoded paths, searching in $PATH
		execvp(cmdname, argv);
		fprintf(stderr, "%s: ", progname);
		perror(cmdname);
		fflush(stdout);
		exit(100);
	}
	while ((n = wait(&status)) != pid && n != -1)
		;
	if (n == -1)
		status = -1;
	if (status&0377) {
		fprintf(stderr, "%s: fatal error in %s\n", progname, cmdname);
		status |= 0400;
	}
	return (status>>8)&0377;
}