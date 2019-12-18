#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct input_dev {int /*<<< orphan*/  absbit; int /*<<< orphan*/  dev; } ;
struct iforce {TYPE_2__* core_effects; TYPE_1__* type; int /*<<< orphan*/  wait; int /*<<< orphan*/  edata; scalar_t__ ecmd; scalar_t__ expect_packet; struct input_dev* dev; } ;
typedef  int __s8 ;
typedef  int __s16 ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/ * btn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_BRAKE ; 
 int /*<<< orphan*/  ABS_GAS ; 
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_HAT1X ; 
 int /*<<< orphan*/  ABS_HAT1Y ; 
 int /*<<< orphan*/  ABS_RUDDER ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_DEAD ; 
 int /*<<< orphan*/  FF_CORE_IS_PLAYED ; 
 int /*<<< orphan*/  FF_STATUS_PLAYING ; 
 int /*<<< orphan*/  FF_STATUS_STOPPED ; 
 int HI (scalar_t__) ; 
 int /*<<< orphan*/  IFORCE_MAX_LENGTH ; 
 int LO (scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_3__* iforce_hat_to_axis ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_ff_status (struct input_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  mark_core_as_ready (struct iforce*,unsigned char) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iforce_process_packet(struct iforce *iforce, u16 cmd, unsigned char *data)
{
	struct input_dev *dev = iforce->dev;
	int i;
	static int being_used = 0;

	if (being_used)
		dev_warn(&iforce->dev->dev,
			 "re-entrant call to iforce_process %d\n", being_used);
	being_used++;

#ifdef CONFIG_JOYSTICK_IFORCE_232
	if (HI(iforce->expect_packet) == HI(cmd)) {
		iforce->expect_packet = 0;
		iforce->ecmd = cmd;
		memcpy(iforce->edata, data, IFORCE_MAX_LENGTH);
	}
#endif
	wake_up(&iforce->wait);

	if (!iforce->type) {
		being_used--;
		return;
	}

	switch (HI(cmd)) {

		case 0x01:	/* joystick position data */
		case 0x03:	/* wheel position data */
			if (HI(cmd) == 1) {
				input_report_abs(dev, ABS_X, (__s16) (((__s16)data[1] << 8) | data[0]));
				input_report_abs(dev, ABS_Y, (__s16) (((__s16)data[3] << 8) | data[2]));
				input_report_abs(dev, ABS_THROTTLE, 255 - data[4]);
				if (LO(cmd) >= 8 && test_bit(ABS_RUDDER ,dev->absbit))
					input_report_abs(dev, ABS_RUDDER, (__s8)data[7]);
			} else {
				input_report_abs(dev, ABS_WHEEL, (__s16) (((__s16)data[1] << 8) | data[0]));
				input_report_abs(dev, ABS_GAS,   255 - data[2]);
				input_report_abs(dev, ABS_BRAKE, 255 - data[3]);
			}

			input_report_abs(dev, ABS_HAT0X, iforce_hat_to_axis[data[6] >> 4].x);
			input_report_abs(dev, ABS_HAT0Y, iforce_hat_to_axis[data[6] >> 4].y);

			for (i = 0; iforce->type->btn[i] >= 0; i++)
				input_report_key(dev, iforce->type->btn[i], data[(i >> 3) + 5] & (1 << (i & 7)));

			/* If there are untouched bits left, interpret them as the second hat */
			if (i <= 8) {
				int btns = data[6];
				if (test_bit(ABS_HAT1X, dev->absbit)) {
					if (btns & 8) input_report_abs(dev, ABS_HAT1X, -1);
					else if (btns & 2) input_report_abs(dev, ABS_HAT1X, 1);
					else input_report_abs(dev, ABS_HAT1X, 0);
				}
				if (test_bit(ABS_HAT1Y, dev->absbit)) {
					if (btns & 1) input_report_abs(dev, ABS_HAT1Y, -1);
					else if (btns & 4) input_report_abs(dev, ABS_HAT1Y, 1);
					else input_report_abs(dev, ABS_HAT1Y, 0);
				}
			}

			input_sync(dev);

			break;

		case 0x02:	/* status report */
			input_report_key(dev, BTN_DEAD, data[0] & 0x02);
			input_sync(dev);

			/* Check if an effect was just started or stopped */
			i = data[1] & 0x7f;
			if (data[1] & 0x80) {
				if (!test_and_set_bit(FF_CORE_IS_PLAYED, iforce->core_effects[i].flags)) {
					/* Report play event */
					input_report_ff_status(dev, i, FF_STATUS_PLAYING);
				}
			} else if (test_and_clear_bit(FF_CORE_IS_PLAYED, iforce->core_effects[i].flags)) {
				/* Report stop event */
				input_report_ff_status(dev, i, FF_STATUS_STOPPED);
			}
			if (LO(cmd) > 3) {
				int j;
				for (j = 3; j < LO(cmd); j += 2)
					mark_core_as_ready(iforce, data[j] | (data[j+1]<<8));
			}
			break;
	}
	being_used--;
}