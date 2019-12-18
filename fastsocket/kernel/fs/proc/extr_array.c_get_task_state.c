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
struct task_struct {unsigned int state; unsigned int exit_state; } ;

/* Variables and functions */
 unsigned int TASK_REPORT ; 
 char** task_state_array ; 

__attribute__((used)) static inline const char *get_task_state(struct task_struct *tsk)
{
	unsigned int state = (tsk->state & TASK_REPORT) | tsk->exit_state;
	const char **p = &task_state_array[0];

	while (state) {
		p++;
		state >>= 1;
	}
	return *p;
}