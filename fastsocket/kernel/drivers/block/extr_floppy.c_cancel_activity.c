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
typedef  int /*<<< orphan*/  work_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  PREPARE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * do_floppy ; 
 scalar_t__ empty ; 
 int /*<<< orphan*/  fd_timer ; 
 int /*<<< orphan*/  floppy_lock ; 
 int /*<<< orphan*/  floppy_work ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cancel_activity(void)
{
	unsigned long flags;

	spin_lock_irqsave(&floppy_lock, flags);
	do_floppy = NULL;
	PREPARE_WORK(&floppy_work, (work_func_t)empty);
	del_timer(&fd_timer);
	spin_unlock_irqrestore(&floppy_lock, flags);
}