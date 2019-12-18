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
struct cafe_camera {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TWSIC1 ; 
 int TWSIC1_ERROR ; 
 int TWSIC1_RVALID ; 
 int cafe_reg_read (struct cafe_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cafe_smbus_read_done(struct cafe_camera *cam)
{
	unsigned long flags;
	int c1;

	/*
	 * We must delay after the interrupt, or the controller gets confused
	 * and never does give us good status.  Fortunately, we don't do this
	 * often.
	 */
	udelay(20);
	spin_lock_irqsave(&cam->dev_lock, flags);
	c1 = cafe_reg_read(cam, REG_TWSIC1);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	return c1 & (TWSIC1_RVALID|TWSIC1_ERROR);
}