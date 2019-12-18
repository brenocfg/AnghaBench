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
typedef  int uint32_t ;
struct proc {int p_memstat_dirty; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int PROC_DIRTY_ALLOWS_IDLE_EXIT ; 
 int PROC_DIRTY_ALLOW_IDLE_EXIT ; 
 int PROC_DIRTY_DEFER ; 
 int PROC_DIRTY_DEFER_ALWAYS ; 
 int PROC_DIRTY_LAUNCH_IN_PROGRESS ; 
 int PROC_DIRTY_TRACK ; 
 int P_DIRTY_TERMINATED ; 

__attribute__((used)) static int
memorystatus_validate_track_flags(struct proc *target_p, uint32_t pcontrol) {
	/* See that the process isn't marked for termination */
	if (target_p->p_memstat_dirty & P_DIRTY_TERMINATED) {
		return EBUSY;
	}
	
	/* Idle exit requires that process be tracked */
	if ((pcontrol & PROC_DIRTY_ALLOW_IDLE_EXIT) &&
	   !(pcontrol & PROC_DIRTY_TRACK)) {
		return EINVAL;
	}

	/* 'Launch in progress' tracking requires that process have enabled dirty tracking too. */
	if ((pcontrol & PROC_DIRTY_LAUNCH_IN_PROGRESS) &&
	   !(pcontrol & PROC_DIRTY_TRACK)) {
		return EINVAL;
	}

	/* Only one type of DEFER behavior is allowed.*/
	if ((pcontrol & PROC_DIRTY_DEFER) && 
	    (pcontrol & PROC_DIRTY_DEFER_ALWAYS)) {
		return EINVAL;
	}

	/* Deferral is only relevant if idle exit is specified */
	if (((pcontrol & PROC_DIRTY_DEFER) ||
	    (pcontrol & PROC_DIRTY_DEFER_ALWAYS)) &&
	   !(pcontrol & PROC_DIRTY_ALLOWS_IDLE_EXIT)) {
		return EINVAL;
	}
	
	return(0);
}