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
struct opt {char* op_value; char* op_name; struct opt* op_next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ COPTS ; 
 int /*<<< orphan*/  VPATH ; 
 char* config_directory ; 
 int /*<<< orphan*/  copy_dependencies (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_files (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  do_machdep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_objs (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  do_rules (int /*<<< orphan*/ *) ; 
 scalar_t__ eq (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * fopenp (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* index (char*,char) ; 
 char* machinename ; 
 scalar_t__ malloc (unsigned int) ; 
 struct opt* mkopt ; 
 struct opt* opt ; 
 char* path (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ profiling ; 
 int /*<<< orphan*/  read_files () ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 char* source_directory ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
makefile(void)
{
	FILE *ifp, *ofp;
	FILE *dfp;
	char pname[BUFSIZ];
	char line[BUFSIZ];
	struct opt *op;

	read_files();
	(void) sprintf(line, "%s/Makefile.template", config_directory);
	ifp = fopenp(VPATH, line, pname, "r");
	if (ifp == 0) {
		perror(line);
		exit(1);
	}
	dfp = fopen(path("Makefile"), "r");
	rename(path("Makefile"), path("Makefile.old"));
	unlink(path("Makefile.old"));
	ofp = fopen(path("Makefile"), "w");
	if (ofp == 0) {
		perror(path("Makefile"));
		exit(1);
	}
	fprintf(ofp, "SOURCE_DIR=%s\n", source_directory);

	fprintf(ofp, "export CONFIG_DEFINES =");
	if (profiling)
		fprintf(ofp, " -DGPROF");

	for (op = opt; op; op = op->op_next)
		if (op->op_value)
			fprintf(ofp, " -D%s=\"%s\"", op->op_name, op->op_value);
		else
			fprintf(ofp, " -D%s", op->op_name);
	fprintf(ofp, "\n");
	for (op = mkopt; op; op = op->op_next)
		if (op->op_value)
			fprintf(ofp, "%s=%s\n", op->op_name, op->op_value);
		else
			fprintf(ofp, "%s\n", op->op_name);

	while (fgets(line, BUFSIZ, ifp) != 0) {
		if (*line == '%')
			goto percent;
		if (profiling && strncmp(line, "COPTS=", 6) == 0) {
			char *cp;
			fprintf(ofp,
				"GPROF.EX=$(SOURCE_DIR)/machdep/%s/gmon.ex\n", machinename);
			cp = index(line, '\n');
			if (cp)
				*cp = 0;
			cp = line + 6;
			while (*cp && (*cp == ' ' || *cp == '\t'))
				cp++;
			COPTS = malloc((unsigned)(strlen(cp) + 1));
			if (COPTS == 0) {
				printf("config: out of memory\n");
				exit(1);
			}
			strcpy(COPTS, cp);
			fprintf(ofp, "%s -pg\n", line);
			continue;
		}
		fprintf(ofp, "%s", line);
		continue;
	percent:
		if (eq(line, "%OBJS\n")) {
			do_objs(ofp, "OBJS=", -1);
		} else if (eq(line, "%CFILES\n")) {
			do_files(ofp, "CFILES=", 'c');
			do_objs(ofp, "COBJS=", 'c');
		} else if (eq(line, "%CXXFILES\n")) {
			do_files(ofp, "CXXFILES=", 'p');
			do_objs(ofp, "CXXOBJS=", 'p');
		} else if (eq(line, "%SFILES\n")) {
			do_files(ofp, "SFILES=", 's');
			do_objs(ofp, "SOBJS=", 's');
		} else if (eq(line, "%MACHDEP\n")) {
			do_machdep(ofp);
		} else if (eq(line, "%RULES\n"))
			do_rules(ofp);
		else
			fprintf(stderr,
			    "Unknown %% construct in generic makefile: %s",
			    line);
	}
	if (dfp != NULL)
	{
		copy_dependencies(dfp, ofp);
		(void) fclose(dfp);
	}
	(void) fclose(ifp);
	(void) fclose(ofp);
}