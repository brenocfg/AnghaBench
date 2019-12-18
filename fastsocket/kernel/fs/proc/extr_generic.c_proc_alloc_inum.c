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

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PROC_DYNAMIC_FIRST ; 
 unsigned int UINT_MAX ; 
 int ida_get_new (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  ida_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  proc_inum_ida ; 
 int /*<<< orphan*/  proc_inum_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int proc_alloc_inum(unsigned int *inum)
{
	unsigned int i;
	int error;

retry:
	if (!ida_pre_get(&proc_inum_ida, GFP_KERNEL))
		return -ENOMEM;

	spin_lock_irq(&proc_inum_lock);
	error = ida_get_new(&proc_inum_ida, &i);
	spin_unlock_irq(&proc_inum_lock);
	if (error == -EAGAIN)
		goto retry;
	else if (error)
		return error;

	if (i > UINT_MAX - PROC_DYNAMIC_FIRST) {
		spin_lock_irq(&proc_inum_lock);
		ida_remove(&proc_inum_ida, i);
		spin_unlock_irq(&proc_inum_lock);
		return -ENOSPC;
	}
	*inum = PROC_DYNAMIC_FIRST + i;
	return 0;
}