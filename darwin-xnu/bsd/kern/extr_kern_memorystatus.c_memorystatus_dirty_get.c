#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int p_memstat_dirty; } ;

/* Variables and functions */
 int PROC_DIRTY_ALLOWS_IDLE_EXIT ; 
 int PROC_DIRTY_IS_DIRTY ; 
 int PROC_DIRTY_LAUNCH_IS_IN_PROGRESS ; 
 int PROC_DIRTY_TRACKED ; 
 int P_DIRTY ; 
 int P_DIRTY_ALLOW_IDLE_EXIT ; 
 int P_DIRTY_LAUNCH_IN_PROGRESS ; 
 int P_DIRTY_TRACK ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

int
memorystatus_dirty_get(proc_t p) {
	int ret = 0;
    
	proc_list_lock();
	
	if (p->p_memstat_dirty & P_DIRTY_TRACK) {
		ret |= PROC_DIRTY_TRACKED;
		if (p->p_memstat_dirty & P_DIRTY_ALLOW_IDLE_EXIT) {
			ret |= PROC_DIRTY_ALLOWS_IDLE_EXIT;
		}
		if (p->p_memstat_dirty & P_DIRTY) {
			ret |= PROC_DIRTY_IS_DIRTY;
		}
		if (p->p_memstat_dirty & P_DIRTY_LAUNCH_IN_PROGRESS) {
			ret |= PROC_DIRTY_LAUNCH_IS_IN_PROGRESS;
		}
	}
	
	proc_list_unlock();
    
	return ret;
}