#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  backgnd; struct nodelist* cmdlist; } ;
union node {TYPE_1__ npipe; } ;
struct nodelist {int /*<<< orphan*/  n; struct nodelist* next; } ;
struct job {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EXIT ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evaltree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exitstatus ; 
 scalar_t__ forkshell (struct job*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct job* makejob (union node*,int) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  prehash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ waitforjob (struct job*,int*) ; 

__attribute__((used)) static void
evalpipe(union node *n)
{
	struct job *jp;
	struct nodelist *lp;
	int pipelen;
	int prevfd;
	int pip[2];

	TRACE(("evalpipe(%p) called\n", (void *)n));
	pipelen = 0;
	for (lp = n->npipe.cmdlist ; lp ; lp = lp->next)
		pipelen++;
	INTOFF;
	jp = makejob(n, pipelen);
	prevfd = -1;
	for (lp = n->npipe.cmdlist ; lp ; lp = lp->next) {
		prehash(lp->n);
		pip[1] = -1;
		if (lp->next) {
			if (pipe(pip) < 0) {
				if (prevfd >= 0)
					close(prevfd);
				error("Pipe call failed: %s", strerror(errno));
			}
		}
		if (forkshell(jp, lp->n, n->npipe.backgnd) == 0) {
			INTON;
			if (prevfd > 0) {
				dup2(prevfd, 0);
				close(prevfd);
			}
			if (pip[1] >= 0) {
				if (!(prevfd >= 0 && pip[0] == 0))
					close(pip[0]);
				if (pip[1] != 1) {
					dup2(pip[1], 1);
					close(pip[1]);
				}
			}
			evaltree(lp->n, EV_EXIT);
		}
		if (prevfd >= 0)
			close(prevfd);
		prevfd = pip[0];
		if (pip[1] != -1)
			close(pip[1]);
	}
	INTON;
	if (n->npipe.backgnd == 0) {
		INTOFF;
		exitstatus = waitforjob(jp, (int *)NULL);
		TRACE(("evalpipe:  job done exit status %d\n", exitstatus));
		INTON;
	} else
		exitstatus = 0;
}