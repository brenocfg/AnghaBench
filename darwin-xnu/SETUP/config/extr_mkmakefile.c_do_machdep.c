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
 int BUFSIZ ; 
 int /*<<< orphan*/  VPATH ; 
 char* config_directory ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopenp (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 char* machinename ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ profiling ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
do_machdep(FILE *ofp)
{
	FILE *ifp;
	char pname[BUFSIZ];
	char line[BUFSIZ];

	(void) sprintf(line, "%s/Makefile.%s", config_directory, machinename);
	ifp = fopenp(VPATH, line, pname, "r");
	if (ifp == 0) {
		perror(line);
		exit(1);
	}
	while (fgets(line, BUFSIZ, ifp) != 0) {
		if (profiling && (strncmp(line, "LIBS=", 5) == 0)) 
			fprintf(ofp,"LIBS=${LIBS_P}\n");
		else
			fputs(line, ofp);
	}
	fclose(ifp);
}