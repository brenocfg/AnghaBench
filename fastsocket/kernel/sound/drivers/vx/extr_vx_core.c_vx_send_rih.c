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
struct vx_core {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vx_send_rih_nolock (struct vx_core*,int) ; 

int vx_send_rih(struct vx_core *chip, int cmd)
{
	unsigned long flags;
	int err;

	spin_lock_irqsave(&chip->lock, flags);
	err = vx_send_rih_nolock(chip, cmd);
	spin_unlock_irqrestore(&chip->lock, flags);
	return err;
}