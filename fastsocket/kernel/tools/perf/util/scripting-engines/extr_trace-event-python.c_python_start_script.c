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
 int PATH_MAX ; 
 int PyRun_SimpleFile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  PySys_SetArgv (int,char**) ; 
 int /*<<< orphan*/  Py_Finalize () ; 
 int /*<<< orphan*/  Py_Initialize () ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int /*<<< orphan*/  initperf_trace_context () ; 
 char** malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int run_start_sub () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int python_start_script(const char *script, int argc, const char **argv)
{
	const char **command_line;
	char buf[PATH_MAX];
	int i, err = 0;
	FILE *fp;

	command_line = malloc((argc + 1) * sizeof(const char *));
	command_line[0] = script;
	for (i = 1; i < argc + 1; i++)
		command_line[i] = argv[i - 1];

	Py_Initialize();

	initperf_trace_context();

	PySys_SetArgv(argc + 1, (char **)command_line);

	fp = fopen(script, "r");
	if (!fp) {
		sprintf(buf, "Can't open python script \"%s\"", script);
		perror(buf);
		err = -1;
		goto error;
	}

	err = PyRun_SimpleFile(fp, script);
	if (err) {
		fprintf(stderr, "Error running python script %s\n", script);
		goto error;
	}

	err = run_start_sub();
	if (err) {
		fprintf(stderr, "Error starting python script %s\n", script);
		goto error;
	}

	free(command_line);

	return err;
error:
	Py_Finalize();
	free(command_line);

	return err;
}