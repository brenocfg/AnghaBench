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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  _SC_PAGE_SIZE ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 int /*<<< orphan*/  debugfs_mount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  handle_internal_command (int,char const**) ; 
 int /*<<< orphan*/  handle_options (char const***,int*,int /*<<< orphan*/ *) ; 
 char* help_unknown_cmd (char const*) ; 
 int /*<<< orphan*/  list_common_cmds_help () ; 
 int /*<<< orphan*/  page_size ; 
 char* perf_extract_argv0_path (char const*) ; 
 char* perf_more_info_string ; 
 char* perf_usage_string ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  pthread__block_sigwinch () ; 
 int run_argv (int*,char const***) ; 
 int /*<<< orphan*/  set_buildid_dir () ; 
 int /*<<< orphan*/  setup_path () ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_attr__init () ; 

int main(int argc, const char **argv)
{
	const char *cmd;

	page_size = sysconf(_SC_PAGE_SIZE);

	cmd = perf_extract_argv0_path(argv[0]);
	if (!cmd)
		cmd = "perf-help";
	/* get debugfs mount point from /proc/mounts */
	debugfs_mount(NULL);
	/*
	 * "perf-xxxx" is the same as "perf xxxx", but we obviously:
	 *
	 *  - cannot take flags in between the "perf" and the "xxxx".
	 *  - cannot execute it externally (since it would just do
	 *    the same thing over again)
	 *
	 * So we just directly call the internal command handler, and
	 * die if that one cannot handle it.
	 */
	if (!prefixcmp(cmd, "perf-")) {
		cmd += 5;
		argv[0] = cmd;
		handle_internal_command(argc, argv);
		die("cannot handle %s internally", cmd);
	}

	/* Look for flags.. */
	argv++;
	argc--;
	handle_options(&argv, &argc, NULL);
	commit_pager_choice();
	set_buildid_dir();

	if (argc > 0) {
		if (!prefixcmp(argv[0], "--"))
			argv[0] += 2;
	} else {
		/* The user didn't specify a command; give them help */
		printf("\n usage: %s\n\n", perf_usage_string);
		list_common_cmds_help();
		printf("\n %s\n\n", perf_more_info_string);
		exit(1);
	}
	cmd = argv[0];

/* RHEL6 - attr tests supported only for x86 */
#if defined(__i386__) || defined(__x86_64)
	test_attr__init();
#endif

	/*
	 * We use PATH to find perf commands, but we prepend some higher
	 * precedence paths: the "--exec-path" option, the PERF_EXEC_PATH
	 * environment, and the $(perfexecdir) from the Makefile at build
	 * time.
	 */
	setup_path();
	/*
	 * Block SIGWINCH notifications so that the thread that wants it can
	 * unblock and get syscalls like select interrupted instead of waiting
	 * forever while the signal goes to some other non interested thread.
	 */
	pthread__block_sigwinch();

	while (1) {
		static int done_help;
		static int was_alias;

		was_alias = run_argv(&argc, &argv);
		if (errno != ENOENT)
			break;

		if (was_alias) {
			fprintf(stderr, "Expansion of alias '%s' failed; "
				"'%s' is not a perf-command\n",
				cmd, argv[0]);
			exit(1);
		}
		if (!done_help) {
			cmd = argv[0] = help_unknown_cmd(cmd);
			done_help = 1;
		} else
			break;
	}

	fprintf(stderr, "Failed to run command '%s': %s\n",
		cmd, strerror(errno));

	return 1;
}