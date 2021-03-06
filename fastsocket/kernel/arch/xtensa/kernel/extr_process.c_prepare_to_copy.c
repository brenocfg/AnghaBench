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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  coprocessor_flush_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 

void prepare_to_copy(struct task_struct *tsk)
{
#if XTENSA_HAVE_COPROCESSORS
	coprocessor_flush_all(task_thread_info(tsk));
#endif
}