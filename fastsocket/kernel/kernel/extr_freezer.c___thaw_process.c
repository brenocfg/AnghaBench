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
struct task_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_FROZEN ; 
 int /*<<< orphan*/  clear_freeze_flag (struct task_struct*) ; 
 scalar_t__ frozen (struct task_struct*) ; 

__attribute__((used)) static int __thaw_process(struct task_struct *p)
{
	if (frozen(p)) {
		p->flags &= ~PF_FROZEN;
		return 1;
	}
	clear_freeze_flag(p);
	return 0;
}