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
 int EIO ; 
 int /*<<< orphan*/  ptrace_do_detach (struct task_struct*,unsigned int) ; 
 int /*<<< orphan*/  utrace_unfreeze_stop (struct task_struct*) ; 
 int /*<<< orphan*/  valid_signal (unsigned int) ; 

int ptrace_detach(struct task_struct *child, unsigned int data)
{
	utrace_unfreeze_stop(child);

	if (!valid_signal(data))
		return -EIO;

	ptrace_do_detach(child, data);

	return 0;
}