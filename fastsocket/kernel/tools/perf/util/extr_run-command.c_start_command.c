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
struct child_process {int in; int out; int err; scalar_t__ pid; int /*<<< orphan*/ * argv; scalar_t__ perf_cmd; int /*<<< orphan*/  (* preexec_cb ) () ;scalar_t__* env; scalar_t__ dir; scalar_t__ stdout_to_stderr; scalar_t__ no_stdout; scalar_t__ no_stderr; scalar_t__ no_stdin; } ;

/* Variables and functions */
 int ENOENT ; 
 int ERR_RUN_COMMAND_EXEC ; 
 int ERR_RUN_COMMAND_FORK ; 
 int ERR_RUN_COMMAND_PIPE ; 
 scalar_t__ chdir (scalar_t__) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  close_pair (int*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  dup_devnull (int) ; 
 int errno ; 
 int /*<<< orphan*/  execv_perf_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,char* const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fork () ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 scalar_t__ strchr (scalar_t__,char) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  unsetenv (scalar_t__) ; 

int start_command(struct child_process *cmd)
{
	int need_in, need_out, need_err;
	int fdin[2], fdout[2], fderr[2];

	/*
	 * In case of errors we must keep the promise to close FDs
	 * that have been passed in via ->in and ->out.
	 */

	need_in = !cmd->no_stdin && cmd->in < 0;
	if (need_in) {
		if (pipe(fdin) < 0) {
			if (cmd->out > 0)
				close(cmd->out);
			return -ERR_RUN_COMMAND_PIPE;
		}
		cmd->in = fdin[1];
	}

	need_out = !cmd->no_stdout
		&& !cmd->stdout_to_stderr
		&& cmd->out < 0;
	if (need_out) {
		if (pipe(fdout) < 0) {
			if (need_in)
				close_pair(fdin);
			else if (cmd->in)
				close(cmd->in);
			return -ERR_RUN_COMMAND_PIPE;
		}
		cmd->out = fdout[0];
	}

	need_err = !cmd->no_stderr && cmd->err < 0;
	if (need_err) {
		if (pipe(fderr) < 0) {
			if (need_in)
				close_pair(fdin);
			else if (cmd->in)
				close(cmd->in);
			if (need_out)
				close_pair(fdout);
			else if (cmd->out)
				close(cmd->out);
			return -ERR_RUN_COMMAND_PIPE;
		}
		cmd->err = fderr[0];
	}

	fflush(NULL);
	cmd->pid = fork();
	if (!cmd->pid) {
		if (cmd->no_stdin)
			dup_devnull(0);
		else if (need_in) {
			dup2(fdin[0], 0);
			close_pair(fdin);
		} else if (cmd->in) {
			dup2(cmd->in, 0);
			close(cmd->in);
		}

		if (cmd->no_stderr)
			dup_devnull(2);
		else if (need_err) {
			dup2(fderr[1], 2);
			close_pair(fderr);
		}

		if (cmd->no_stdout)
			dup_devnull(1);
		else if (cmd->stdout_to_stderr)
			dup2(2, 1);
		else if (need_out) {
			dup2(fdout[1], 1);
			close_pair(fdout);
		} else if (cmd->out > 1) {
			dup2(cmd->out, 1);
			close(cmd->out);
		}

		if (cmd->dir && chdir(cmd->dir))
			die("exec %s: cd to %s failed (%s)", cmd->argv[0],
			    cmd->dir, strerror(errno));
		if (cmd->env) {
			for (; *cmd->env; cmd->env++) {
				if (strchr(*cmd->env, '='))
					putenv((char*)*cmd->env);
				else
					unsetenv(*cmd->env);
			}
		}
		if (cmd->preexec_cb)
			cmd->preexec_cb();
		if (cmd->perf_cmd) {
			execv_perf_cmd(cmd->argv);
		} else {
			execvp(cmd->argv[0], (char *const*) cmd->argv);
		}
		exit(127);
	}

	if (cmd->pid < 0) {
		int err = errno;
		if (need_in)
			close_pair(fdin);
		else if (cmd->in)
			close(cmd->in);
		if (need_out)
			close_pair(fdout);
		else if (cmd->out)
			close(cmd->out);
		if (need_err)
			close_pair(fderr);
		return err == ENOENT ?
			-ERR_RUN_COMMAND_EXEC :
			-ERR_RUN_COMMAND_FORK;
	}

	if (need_in)
		close(fdin[0]);
	else if (cmd->in)
		close(cmd->in);

	if (need_out)
		close(fdout[1]);
	else if (cmd->out)
		close(cmd->out);

	if (need_err)
		close(fderr[1]);

	return 0;
}