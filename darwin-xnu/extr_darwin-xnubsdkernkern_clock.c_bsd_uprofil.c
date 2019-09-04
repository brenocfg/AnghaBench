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
typedef  int /*<<< orphan*/  user_addr_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct time_value {int seconds; int microseconds; } ;
struct proc {int p_flag; TYPE_2__* p_stats; } ;
struct TYPE_3__ {struct timeval ru_stime; } ;
struct TYPE_4__ {TYPE_1__ p_ru; } ;

/* Variables and functions */
 int P_PROFIL ; 
 int /*<<< orphan*/  addupc_task (struct proc*,int /*<<< orphan*/ ,int) ; 
 struct proc* current_proc () ; 
 int tick ; 

void
bsd_uprofil(struct time_value *syst, user_addr_t pc)
{
	struct proc *p = current_proc();
	int		ticks;
	struct timeval	*tv;
	struct timeval st;

	if (p == NULL)
	        return;
	if ( !(p->p_flag & P_PROFIL))
	        return;

	st.tv_sec = syst->seconds;
	st.tv_usec = syst->microseconds;

	tv = &(p->p_stats->p_ru.ru_stime);

	ticks = ((tv->tv_sec - st.tv_sec) * 1000 +
		(tv->tv_usec - st.tv_usec) / 1000) /
		(tick / 1000);
	if (ticks)
		addupc_task(p, pc, ticks);
}