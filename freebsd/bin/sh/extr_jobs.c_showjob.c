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
struct procstat {char const* cmd; scalar_t__ pid; int /*<<< orphan*/  status; } ;
struct job {int nprocs; scalar_t__ state; struct procstat* ps; } ;
typedef  int /*<<< orphan*/  statebuf ;

/* Variables and functions */
 scalar_t__ JOBSTOPPED ; 
 int SHOWJOBS_PGIDS ; 
 int SHOWJOBS_PIDS ; 
 int SHOWJOBS_VERBOSE ; 
 scalar_t__ WCOREDUMP (int) ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSTOPPED (int /*<<< orphan*/ ) ; 
 int WSTOPSIG (int /*<<< orphan*/ ) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  fmtstr (char*,int,char*,int,...) ; 
 struct job* getcurjob (struct job*) ; 
 int getjobstatus (struct job*) ; 
 struct job* jobtab ; 
 int /*<<< orphan*/  out1c (char) ; 
 int /*<<< orphan*/  out1fmt (char*,int) ; 
 int /*<<< orphan*/  out1str (char const*) ; 
 int /*<<< orphan*/  printjobcmd (struct job*) ; 
 int strlen (char const*) ; 
 char* strsignal (int) ; 

__attribute__((used)) static void
showjob(struct job *jp, int mode)
{
	char s[64];
	char statebuf[16];
	const char *statestr, *coredump;
	struct procstat *ps;
	struct job *j;
	int col, curr, i, jobno, prev, procno, status;
	char c;

	procno = (mode == SHOWJOBS_PGIDS) ? 1 : jp->nprocs;
	jobno = jp - jobtab + 1;
	curr = prev = 0;
#if JOBS
	if ((j = getcurjob(NULL)) != NULL) {
		curr = j - jobtab + 1;
		if ((j = getcurjob(j)) != NULL)
			prev = j - jobtab + 1;
	}
#endif
	coredump = "";
	status = getjobstatus(jp);
	if (jp->state == 0) {
		statestr = "Running";
#if JOBS
	} else if (jp->state == JOBSTOPPED) {
		ps = jp->ps + jp->nprocs - 1;
		while (!WIFSTOPPED(ps->status) && ps > jp->ps)
			ps--;
		if (WIFSTOPPED(ps->status))
			i = WSTOPSIG(ps->status);
		else
			i = -1;
		statestr = strsignal(i);
		if (statestr == NULL)
			statestr = "Suspended";
#endif
	} else if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == 0)
			statestr = "Done";
		else {
			fmtstr(statebuf, sizeof(statebuf), "Done(%d)",
			    WEXITSTATUS(status));
			statestr = statebuf;
		}
	} else {
		i = WTERMSIG(status);
		statestr = strsignal(i);
		if (statestr == NULL)
			statestr = "Unknown signal";
		if (WCOREDUMP(status))
			coredump = " (core dumped)";
	}

	for (ps = jp->ps ; procno > 0 ; ps++, procno--) { /* for each process */
		if (mode == SHOWJOBS_PIDS || mode == SHOWJOBS_PGIDS) {
			out1fmt("%d\n", (int)ps->pid);
			continue;
		}
		if (mode != SHOWJOBS_VERBOSE && ps != jp->ps)
			continue;
		if (jobno == curr && ps == jp->ps)
			c = '+';
		else if (jobno == prev && ps == jp->ps)
			c = '-';
		else
			c = ' ';
		if (ps == jp->ps)
			fmtstr(s, 64, "[%d] %c ", jobno, c);
		else
			fmtstr(s, 64, "    %c ", c);
		out1str(s);
		col = strlen(s);
		if (mode == SHOWJOBS_VERBOSE) {
			fmtstr(s, 64, "%d ", (int)ps->pid);
			out1str(s);
			col += strlen(s);
		}
		if (ps == jp->ps) {
			out1str(statestr);
			out1str(coredump);
			col += strlen(statestr) + strlen(coredump);
		}
		do {
			out1c(' ');
			col++;
		} while (col < 30);
		if (mode == SHOWJOBS_VERBOSE) {
			out1str(ps->cmd);
			out1c('\n');
		} else
			printjobcmd(jp);
	}
}