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
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int GPIO_BITSY_NPOWER_BUTTON ; 
 int GPLR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_SUSPEND ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static irqreturn_t npower_button_handler(int irq, void *dev_id)
{
	int down = (GPLR & GPIO_BITSY_NPOWER_BUTTON) ? 0 : 1;
	struct input_dev *dev = dev_id;

	/*
	 * This interrupt is only called when we release the key. So we have
	 * to fake a key press.
	 */
	input_report_key(dev, KEY_SUSPEND, 1);
	input_report_key(dev, KEY_SUSPEND, down);
	input_sync(dev);

	return IRQ_HANDLED;
}