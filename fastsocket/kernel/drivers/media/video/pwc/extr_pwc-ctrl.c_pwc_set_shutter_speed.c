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
struct pwc_device {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC2 (int /*<<< orphan*/ ) ; 
 scalar_t__ DEVICE_USE_CODEC3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRESET_SHUTTER_FORMATTER ; 
 int /*<<< orphan*/  SET_LUM_CTL ; 
 int /*<<< orphan*/  SHUTTER_MODE_FORMATTER ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int) ; 

int pwc_set_shutter_speed(struct pwc_device *pdev, int mode, int value)
{
	char buf[2];
	int speed, ret;


	if (mode)
		buf[0] = 0x0;	/* auto */
	else
		buf[0] = 0xff; /* fixed */

	ret = send_control_msg(pdev,
		SET_LUM_CTL, SHUTTER_MODE_FORMATTER, &buf, 1);

	if (!mode && ret >= 0) {
		if (value < 0)
			value = 0;
		if (value > 0xffff)
			value = 0xffff;

		if (DEVICE_USE_CODEC2(pdev->type)) {
			/* speed ranges from 0x0 to 0x290 (656) */
			speed = (value / 100);
			buf[1] = speed >> 8;
			buf[0] = speed & 0xff;
		} else if (DEVICE_USE_CODEC3(pdev->type)) {
			/* speed seems to range from 0x0 to 0xff */
			buf[1] = 0;
			buf[0] = value >> 8;
		}

		ret = send_control_msg(pdev,
			SET_LUM_CTL, PRESET_SHUTTER_FORMATTER,
			&buf, sizeof(buf));
	}
	return ret;
}