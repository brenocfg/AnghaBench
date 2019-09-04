#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* processor_set_t ;
struct TYPE_5__ {int /*<<< orphan*/  rt_runq; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__ pset0 ; 
 void pset_rt_init (TYPE_1__*) ; 

void
sched_rtglobal_init(processor_set_t pset)
{
	if (pset == &pset0) {
		return pset_rt_init(pset);
	}

	/* Only pset0 rt_runq is used, so make it easy to detect
	 * buggy accesses to others.
	 */
	memset(&pset->rt_runq, 0xfd, sizeof pset->rt_runq);
}