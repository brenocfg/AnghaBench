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
struct task_struct {unsigned long flags; } ;

/* Variables and functions */
 unsigned long PF_FORKNOEXEC ; 
 unsigned long PF_STARTING ; 
 unsigned long PF_SUPERPRIV ; 
 int /*<<< orphan*/  clear_freeze_flag (struct task_struct*) ; 

__attribute__((used)) static void copy_flags(unsigned long clone_flags, struct task_struct *p)
{
	unsigned long new_flags = p->flags;

	new_flags &= ~PF_SUPERPRIV;
	new_flags |= PF_FORKNOEXEC;
	new_flags |= PF_STARTING;
	p->flags = new_flags;
	clear_freeze_flag(p);
}