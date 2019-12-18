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
struct cafe_camera {int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  smbus_wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int ALLIRQS ; 
 unsigned int FRAMEIRQS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  REG_IRQSTAT ; 
 unsigned int TWSIIRQS ; 
 int /*<<< orphan*/  cafe_frame_irq (struct cafe_camera*,unsigned int) ; 
 unsigned int cafe_reg_read (struct cafe_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_reg_write (struct cafe_camera*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cafe_irq(int irq, void *data)
{
	struct cafe_camera *cam = data;
	unsigned int irqs;

	spin_lock(&cam->dev_lock);
	irqs = cafe_reg_read(cam, REG_IRQSTAT);
	if ((irqs & ALLIRQS) == 0) {
		spin_unlock(&cam->dev_lock);
		return IRQ_NONE;
	}
	if (irqs & FRAMEIRQS)
		cafe_frame_irq(cam, irqs);
	if (irqs & TWSIIRQS) {
		cafe_reg_write(cam, REG_IRQSTAT, TWSIIRQS);
		wake_up(&cam->smbus_wait);
	}
	spin_unlock(&cam->dev_lock);
	return IRQ_HANDLED;
}