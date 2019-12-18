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
typedef  int /*<<< orphan*/  unaligned_u64 ;
typedef  TYPE_3__* proc_t ;
struct TYPE_5__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {TYPE_2__* p_stats; TYPE_1__ p_start; } ;
struct TYPE_6__ {int /*<<< orphan*/  ps_start; } ;

/* Variables and functions */
 TYPE_3__* PROC_NULL ; 

void
proc_starttime_kdp(void *p, unaligned_u64 *tv_sec, unaligned_u64 *tv_usec, unaligned_u64 *abstime)
{
	proc_t pp = (proc_t)p;
	if (pp != PROC_NULL) {
		if (tv_sec != NULL)
			*tv_sec = pp->p_start.tv_sec;
		if (tv_usec != NULL)
			*tv_usec = pp->p_start.tv_usec;
		if (abstime != NULL) {
			if (pp->p_stats != NULL)
				*abstime = pp->p_stats->ps_start;
			else
				*abstime = 0;
		}
	}
}