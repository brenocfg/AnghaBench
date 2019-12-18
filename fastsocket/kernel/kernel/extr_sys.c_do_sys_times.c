#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tms {void* tms_cstime; void* tms_cutime; void* tms_stime; void* tms_utime; } ;
typedef  int /*<<< orphan*/  cputime_t ;
struct TYPE_7__ {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_6__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_5__ {int /*<<< orphan*/  cstime; int /*<<< orphan*/  cutime; } ;

/* Variables and functions */
 void* cputime_to_clock_t (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_group_times (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void do_sys_times(struct tms *tms)
{
	cputime_t tgutime, tgstime, cutime, cstime;

	spin_lock_irq(&current->sighand->siglock);
	thread_group_times(current, &tgutime, &tgstime);
	cutime = current->signal->cutime;
	cstime = current->signal->cstime;
	spin_unlock_irq(&current->sighand->siglock);
	tms->tms_utime = cputime_to_clock_t(tgutime);
	tms->tms_stime = cputime_to_clock_t(tgstime);
	tms->tms_cutime = cputime_to_clock_t(cutime);
	tms->tms_cstime = cputime_to_clock_t(cstime);
}