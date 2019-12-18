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
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {scalar_t__ p_pid; scalar_t__ p_stat; scalar_t__ p_slptime; int /*<<< orphan*/  p_estcpu; } ;

/* Variables and functions */
#define  BOTH 130 
 int ISRUN (TYPE_1__*) ; 
#define  ONLYA 129 
#define  ONLYB 128 
 scalar_t__ SZOMB ; 
 int TESTAB (int,int) ; 

__attribute__((used)) static int
proc_compare(proc_t p1, proc_t p2)
{
	/* NOTE THIS FN needs to be NON BLOCKING */

	if (p1 == NULL)
		return (1);
	/*
	 * see if at least one of them is runnable
	 */
	switch (TESTAB(ISRUN(p1), ISRUN(p2))) {
	case ONLYA:
		return (0);
	case ONLYB:
		return (1);
	case BOTH:
		/*
		 * tie - favor one with highest recent cpu utilization
		 */
#ifdef _PROC_HAS_SCHEDINFO_
		/* Without the support the fields are always zero */
		if (p2->p_estcpu > p1->p_estcpu)
			return (1);
		if (p1->p_estcpu > p2->p_estcpu)
			return (0);
#endif /* _PROC_HAS_SCHEDINFO_ */
		return (p2->p_pid > p1->p_pid);	/* tie - return highest pid */
	}
	/*
 	 * weed out zombies
	 */
	switch (TESTAB(p1->p_stat == SZOMB, p2->p_stat == SZOMB)) {
	case ONLYA:
		return (1);
	case ONLYB:
		return (0);
	case BOTH:
		return (p2->p_pid > p1->p_pid); /* tie - return highest pid */
	}
	/*
	 * pick the one with the smallest sleep time
	 */
#ifdef _PROC_HAS_SCHEDINFO_
	/* Without the support the fields are always zero */
	if (p2->p_slptime > p1->p_slptime)
		return (0);
	if (p1->p_slptime > p2->p_slptime)
		return (1);
#endif /* _PROC_HAS_SCHEDINFO_ */
	return (p2->p_pid > p1->p_pid);		/* tie - return highest pid */
}