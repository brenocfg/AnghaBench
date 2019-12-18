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
struct h3600_dev {int dummy; } ;

/* Variables and functions */
#define  EV_LED 128 
 struct h3600_dev* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int h3600ts_event(struct input_dev *dev, unsigned int type,
			 unsigned int code, int value)
{
#if 0
	struct h3600_dev *ts = input_get_drvdata(dev);

	switch (type) {
		case EV_LED: {
		//	serio_write(ts->serio, SOME_CMD);
			return 0;
		}
	}
	return -1;
#endif
	return 0;
}