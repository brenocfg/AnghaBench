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
typedef  long uint64_t ;
struct proc {long p_pid; long p_uniqueid; } ;

/* Variables and functions */

void
kdbg_trace_data(struct proc *proc, long *arg_pid, long *arg_uniqueid)
{
	if (!proc) { 
		*arg_pid = 0;
		*arg_uniqueid = 0; 
	} else { 
		*arg_pid = proc->p_pid;
		*arg_uniqueid = proc->p_uniqueid;
		if ((uint64_t) *arg_uniqueid != proc->p_uniqueid) { 
			*arg_uniqueid = 0; 
		}
	}
}