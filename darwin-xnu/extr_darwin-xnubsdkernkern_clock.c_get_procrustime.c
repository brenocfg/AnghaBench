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
struct TYPE_7__ {int /*<<< orphan*/  microseconds; int /*<<< orphan*/  seconds; } ;
typedef  TYPE_3__ time_value_t ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct proc {int p_flag; TYPE_2__* p_stats; } ;
struct TYPE_5__ {struct timeval ru_stime; } ;
struct TYPE_6__ {TYPE_1__ p_ru; } ;

/* Variables and functions */
 int P_PROFIL ; 
 struct proc* current_proc () ; 

void
get_procrustime(time_value_t *tv)
{
	struct proc *p = current_proc();
	struct timeval st;

	if (p == NULL) 
		return;
	if ( !(p->p_flag & P_PROFIL))
	        return;

	//proc_lock(p);
	st = p->p_stats->p_ru.ru_stime;
	//proc_unlock(p);
	
	tv->seconds = st.tv_sec;
	tv->microseconds = st.tv_usec;
}