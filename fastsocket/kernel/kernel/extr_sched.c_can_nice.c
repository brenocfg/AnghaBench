#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_2__* signal; } ;
struct TYPE_4__ {TYPE_1__* rlim; } ;
struct TYPE_3__ {int rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 size_t RLIMIT_NICE ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 

int can_nice(const struct task_struct *p, const int nice)
{
	/* convert nice value [19,-20] to rlimit style value [1,40] */
	int nice_rlim = 20 - nice;

	return (nice_rlim <= p->signal->rlim[RLIMIT_NICE].rlim_cur ||
		capable(CAP_SYS_NICE));
}