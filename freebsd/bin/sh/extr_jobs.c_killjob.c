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
struct job {scalar_t__ state; int nprocs; TYPE_1__* ps; scalar_t__ jobctl; } ;
struct TYPE_2__ {int status; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESRCH ; 
 scalar_t__ JOBDONE ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int /*<<< orphan*/  errno ; 
 struct job* getjob (char const*) ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int) ; 

int
killjob(const char *name, int sig)
{
	struct job *jp;
	int i, ret;

	jp = getjob(name);
	if (jp->state == JOBDONE)
		return 0;
	if (jp->jobctl)
		return kill(-jp->ps[0].pid, sig);
	ret = -1;
	errno = ESRCH;
	for (i = 0; i < jp->nprocs; i++)
		if (jp->ps[i].status == -1 || WIFSTOPPED(jp->ps[i].status)) {
			if (kill(jp->ps[i].pid, sig) == 0)
				ret = 0;
		} else
			ret = 0;
	return ret;
}