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
struct strbuf {char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int ERR_RUN_COMMAND_EXEC ; 
 scalar_t__ IS_RUN_COMMAND_ERR (int) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void execv_dashed_external(const char **argv)
{
	struct strbuf cmd = STRBUF_INIT;
	const char *tmp;
	int status;

	strbuf_addf(&cmd, "perf-%s", argv[0]);

	/*
	 * argv[0] must be the perf command, but the argv array
	 * belongs to the caller, and may be reused in
	 * subsequent loop iterations. Save argv[0] and
	 * restore it on error.
	 */
	tmp = argv[0];
	argv[0] = cmd.buf;

	/*
	 * if we fail because the command is not found, it is
	 * OK to return. Otherwise, we just pass along the status code.
	 */
	status = run_command_v_opt(argv, 0);
	if (status != -ERR_RUN_COMMAND_EXEC) {
		if (IS_RUN_COMMAND_ERR(status))
			die("unable to run '%s'", argv[0]);
		exit(-status);
	}
	errno = ENOENT; /* as if we called execvp */

	argv[0] = tmp;

	strbuf_release(&cmd);
}