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
struct highlander_i2c_dev {int /*<<< orphan*/  cmd_complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  highlander_i2c_done (struct highlander_i2c_dev*) ; 

__attribute__((used)) static irqreturn_t highlander_i2c_irq(int irq, void *dev_id)
{
	struct highlander_i2c_dev *dev = dev_id;

	highlander_i2c_done(dev);
	complete(&dev->cmd_complete);

	return IRQ_HANDLED;
}