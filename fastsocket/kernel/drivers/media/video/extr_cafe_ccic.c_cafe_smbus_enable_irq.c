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
 int /*<<< orphan*/  REG_IRQMASK ; 
 int /*<<< orphan*/  TWSIIRQS ; 
 int /*<<< orphan*/  cafe_reg_set_bit (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cafe_smbus_enable_irq(struct cafe_camera *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->dev_lock, flags);
	cafe_reg_set_bit(cam, REG_IRQMASK, TWSIIRQS);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
}