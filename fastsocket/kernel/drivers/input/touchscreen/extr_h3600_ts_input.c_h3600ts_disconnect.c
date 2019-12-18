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
struct serio {int dummy; } ;
struct h3600_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_GPIO_BITSY_ACTION_BUTTON ; 
 int /*<<< orphan*/  IRQ_GPIO_BITSY_NPOWER_BUTTON ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct h3600_dev*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct h3600_dev* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void h3600ts_disconnect(struct serio *serio)
{
	struct h3600_dev *ts = serio_get_drvdata(serio);

	free_irq(IRQ_GPIO_BITSY_ACTION_BUTTON, &ts->dev);
	free_irq(IRQ_GPIO_BITSY_NPOWER_BUTTON, &ts->dev);
	input_get_device(ts->dev);
	input_unregister_device(ts->dev);
	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	input_put_device(ts->dev);
	kfree(ts);
}