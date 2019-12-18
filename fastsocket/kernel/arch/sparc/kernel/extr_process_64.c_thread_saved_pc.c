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
struct thread_info {scalar_t__ ksp; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ STACK_BIAS ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

unsigned long thread_saved_pc(struct task_struct *tsk)
{
	struct thread_info *ti = task_thread_info(tsk);
	unsigned long ret = 0xdeadbeefUL;
	
	if (ti && ti->ksp) {
		unsigned long *sp;
		sp = (unsigned long *)(ti->ksp + STACK_BIAS);
		if (((unsigned long)sp & (sizeof(long) - 1)) == 0UL &&
		    sp[14]) {
			unsigned long *fp;
			fp = (unsigned long *)(sp[14] + STACK_BIAS);
			if (((unsigned long)fp & (sizeof(long) - 1)) == 0UL)
				ret = fp[15];
		}
	}
	return ret;
}