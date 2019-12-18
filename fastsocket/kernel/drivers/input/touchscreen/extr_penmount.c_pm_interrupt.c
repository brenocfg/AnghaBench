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
struct pm {unsigned char* data; size_t idx; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 size_t PM_MAX_LENGTH ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 struct pm* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t pm_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct pm *pm = serio_get_drvdata(serio);
	struct input_dev *dev = pm->dev;

	pm->data[pm->idx] = data;

	if (pm->data[0] & 0x80) {
		if (PM_MAX_LENGTH == ++pm->idx) {
			input_report_abs(dev, ABS_X, pm->data[2] * 128 + pm->data[1]);
			input_report_abs(dev, ABS_Y, pm->data[4] * 128 + pm->data[3]);
			input_report_key(dev, BTN_TOUCH, !!(pm->data[0] & 0x40));
			input_sync(dev);
			pm->idx = 0;
		}
	}

	return IRQ_HANDLED;
}