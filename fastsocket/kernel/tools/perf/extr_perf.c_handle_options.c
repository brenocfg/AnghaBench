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
struct cmd_struct {char* cmd; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct cmd_struct*) ; 
 int /*<<< orphan*/  CMD_DEBUGFS_DIR ; 
 int /*<<< orphan*/  CMD_EXEC_PATH ; 
 int /*<<< orphan*/  CMD_PERF_DIR ; 
 int /*<<< orphan*/  CMD_WORK_TREE ; 
 int /*<<< orphan*/  PERF_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  PERF_HTML_PATH ; 
 int /*<<< orphan*/  PERF_WORK_TREE_ENVIRONMENT ; 
 struct cmd_struct* commands ; 
 char* debugfs_mountpoint ; 
 int /*<<< orphan*/  debugfs_set_path (char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perf_exec_path () ; 
 int /*<<< orphan*/  perf_set_argv_exec_path (char const*) ; 
 int /*<<< orphan*/  perf_usage_string ; 
 int /*<<< orphan*/  prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int use_pager ; 

__attribute__((used)) static int handle_options(const char ***argv, int *argc, int *envchanged)
{
	int handled = 0;

	while (*argc > 0) {
		const char *cmd = (*argv)[0];
		if (cmd[0] != '-')
			break;

		/*
		 * For legacy reasons, the "version" and "help"
		 * commands can be written with "--" prepended
		 * to make them look like flags.
		 */
		if (!strcmp(cmd, "--help") || !strcmp(cmd, "--version"))
			break;

		/*
		 * Check remaining flags.
		 */
		if (!prefixcmp(cmd, CMD_EXEC_PATH)) {
			cmd += strlen(CMD_EXEC_PATH);
			if (*cmd == '=')
				perf_set_argv_exec_path(cmd + 1);
			else {
				puts(perf_exec_path());
				exit(0);
			}
		} else if (!strcmp(cmd, "--html-path")) {
			puts(system_path(PERF_HTML_PATH));
			exit(0);
		} else if (!strcmp(cmd, "-p") || !strcmp(cmd, "--paginate")) {
			use_pager = 1;
		} else if (!strcmp(cmd, "--no-pager")) {
			use_pager = 0;
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--perf-dir")) {
			if (*argc < 2) {
				fprintf(stderr, "No directory given for --perf-dir.\n");
				usage(perf_usage_string);
			}
			setenv(PERF_DIR_ENVIRONMENT, (*argv)[1], 1);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
			handled++;
		} else if (!prefixcmp(cmd, CMD_PERF_DIR)) {
			setenv(PERF_DIR_ENVIRONMENT, cmd + strlen(CMD_PERF_DIR), 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--work-tree")) {
			if (*argc < 2) {
				fprintf(stderr, "No directory given for --work-tree.\n");
				usage(perf_usage_string);
			}
			setenv(PERF_WORK_TREE_ENVIRONMENT, (*argv)[1], 1);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		} else if (!prefixcmp(cmd, CMD_WORK_TREE)) {
			setenv(PERF_WORK_TREE_ENVIRONMENT, cmd + strlen(CMD_WORK_TREE), 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--debugfs-dir")) {
			if (*argc < 2) {
				fprintf(stderr, "No directory given for --debugfs-dir.\n");
				usage(perf_usage_string);
			}
			debugfs_set_path((*argv)[1]);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		} else if (!prefixcmp(cmd, CMD_DEBUGFS_DIR)) {
			debugfs_set_path(cmd + strlen(CMD_DEBUGFS_DIR));
			fprintf(stderr, "dir: %s\n", debugfs_mountpoint);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--list-cmds")) {
			unsigned int i;

			for (i = 0; i < ARRAY_SIZE(commands); i++) {
				struct cmd_struct *p = commands+i;
				printf("%s ", p->cmd);
			}
			exit(0);
		} else {
			fprintf(stderr, "Unknown option: %s\n", cmd);
			usage(perf_usage_string);
		}

		(*argv)++;
		(*argc)--;
		handled++;
	}
	return handled;
}