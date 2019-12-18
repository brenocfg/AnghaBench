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
 int /*<<< orphan*/  DEBUG_ARCH ; 
 int /*<<< orphan*/  DEBUG_COND ; 
 int /*<<< orphan*/  DEBUG_CWD ; 
 int /*<<< orphan*/  DEBUG_DIR ; 
 int /*<<< orphan*/  DEBUG_ERROR ; 
 int /*<<< orphan*/  DEBUG_FOR ; 
 int /*<<< orphan*/  DEBUG_GRAPH1 ; 
 int /*<<< orphan*/  DEBUG_GRAPH2 ; 
 int /*<<< orphan*/  DEBUG_GRAPH3 ; 
 int /*<<< orphan*/  DEBUG_JOB ; 
 int /*<<< orphan*/  DEBUG_LOUD ; 
 int /*<<< orphan*/  DEBUG_MAKE ; 
 int /*<<< orphan*/  DEBUG_META ; 
 int /*<<< orphan*/  DEBUG_PARSE ; 
 int /*<<< orphan*/  DEBUG_SCRIPT ; 
 int /*<<< orphan*/  DEBUG_SHELL ; 
 int /*<<< orphan*/  DEBUG_SUFF ; 
 int /*<<< orphan*/  DEBUG_TARG ; 
 int /*<<< orphan*/  DEBUG_VAR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  _IONBF ; 
 char* bmake_malloc (int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  debugVflag ; 
 scalar_t__ debug_file ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (char*,char const*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  setvbuf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
parse_debug_options(const char *argvalue)
{
	const char *modules;
	const char *mode;
	char *fname;
	int len;

	for (modules = argvalue; *modules; ++modules) {
		switch (*modules) {
		case 'A':
			debug = ~0;
			break;
		case 'a':
			debug |= DEBUG_ARCH;
			break;
		case 'C':
			debug |= DEBUG_CWD;
			break;
		case 'c':
			debug |= DEBUG_COND;
			break;
		case 'd':
			debug |= DEBUG_DIR;
			break;
		case 'e':
			debug |= DEBUG_ERROR;
			break;
		case 'f':
			debug |= DEBUG_FOR;
			break;
		case 'g':
			if (modules[1] == '1') {
				debug |= DEBUG_GRAPH1;
				++modules;
			}
			else if (modules[1] == '2') {
				debug |= DEBUG_GRAPH2;
				++modules;
			}
			else if (modules[1] == '3') {
				debug |= DEBUG_GRAPH3;
				++modules;
			}
			break;
		case 'j':
			debug |= DEBUG_JOB;
			break;
		case 'l':
			debug |= DEBUG_LOUD;
			break;
		case 'M':
			debug |= DEBUG_META;
			break;
		case 'm':
			debug |= DEBUG_MAKE;
			break;
		case 'n':
			debug |= DEBUG_SCRIPT;
			break;
		case 'p':
			debug |= DEBUG_PARSE;
			break;
		case 's':
			debug |= DEBUG_SUFF;
			break;
		case 't':
			debug |= DEBUG_TARG;
			break;
		case 'V':
			debugVflag = TRUE;
			break;
		case 'v':
			debug |= DEBUG_VAR;
			break;
		case 'x':
			debug |= DEBUG_SHELL;
			break;
		case 'F':
			if (debug_file != stdout && debug_file != stderr)
				fclose(debug_file);
			if (*++modules == '+') {
				modules++;
				mode = "a";
			} else
				mode = "w";
			if (strcmp(modules, "stdout") == 0) {
				debug_file = stdout;
				goto debug_setbuf;
			}
			if (strcmp(modules, "stderr") == 0) {
				debug_file = stderr;
				goto debug_setbuf;
			}
			len = strlen(modules);
			fname = bmake_malloc(len + 20);
			memcpy(fname, modules, len + 1);
			/* Let the filename be modified by the pid */
			if (strcmp(fname + len - 3, ".%d") == 0)
				snprintf(fname + len - 2, 20, "%d", getpid());
			debug_file = fopen(fname, mode);
			if (!debug_file) {
				fprintf(stderr, "Cannot open debug file %s\n",
				    fname);
				usage();
			}
			free(fname);
			goto debug_setbuf;
		default:
			(void)fprintf(stderr,
			    "%s: illegal argument to d option -- %c\n",
			    progname, *modules);
			usage();
		}
	}
debug_setbuf:
	/*
	 * Make the debug_file unbuffered, and make
	 * stdout line buffered (unless debugfile == stdout).
	 */
	setvbuf(debug_file, NULL, _IONBF, 0);
	if (debug_file != stdout) {
		setvbuf(stdout, NULL, _IOLBF, 0);
	}
}