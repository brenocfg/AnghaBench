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
 int GPIO_BITSY_ACTION_BUTTON ; 
 int GPLR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_ENTER ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static irqreturn_t action_button_handler(int irq, void *dev_id)
{
	int down = (GPLR & GPIO_BITSY_ACTION_BUTTON) ? 0 : 1;
	struct input_dev *dev = dev_id;

	input_report_key(dev, KEY_ENTER, down);
	input_sync(dev);

	return IRQ_HANDLED;
}