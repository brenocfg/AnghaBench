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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct cmd_struct {int option; int (* fn ) (int,char const**,char const*) ;int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int RUN_SETUP ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int USE_PAGER ; 
 int check_browser_config (int /*<<< orphan*/ ) ; 
 int check_pager_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit_browser (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int stub1 (int,char const**,char const*) ; 
 int use_browser ; 
 int use_pager ; 

__attribute__((used)) static int run_builtin(struct cmd_struct *p, int argc, const char **argv)
{
	int status;
	struct stat st;
	const char *prefix;

	prefix = NULL;
	if (p->option & RUN_SETUP)
		prefix = NULL; /* setup_perf_directory(); */

	if (use_browser == -1)
		use_browser = check_browser_config(p->cmd);

	if (use_pager == -1 && p->option & RUN_SETUP)
		use_pager = check_pager_config(p->cmd);
	if (use_pager == -1 && p->option & USE_PAGER)
		use_pager = 1;
	commit_pager_choice();

	status = p->fn(argc, argv, prefix);
	exit_browser(status);

	if (status)
		return status & 0xff;

	/* Somebody closed stdout? */
	if (fstat(fileno(stdout), &st))
		return 0;
	/* Ignore write errors for pipes and sockets.. */
	if (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode))
		return 0;

	/* Check for ENOSPC and EIO errors.. */
	if (fflush(stdout))
		die("write failure on standard output: %s", strerror(errno));
	if (ferror(stdout))
		die("unknown write failure on standard output");
	if (fclose(stdout))
		die("close failed on standard output: %s", strerror(errno));
	return 0;
}