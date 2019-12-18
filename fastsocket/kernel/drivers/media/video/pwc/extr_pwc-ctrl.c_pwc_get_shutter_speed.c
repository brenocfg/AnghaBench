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
 int /*<<< orphan*/  GET_STATUS_CTL ; 
 int /*<<< orphan*/  READ_SHUTTER_FORMATTER ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**,int) ; 

int pwc_get_shutter_speed(struct pwc_device *pdev, int *value)
{
	unsigned char buf[2];
	int ret;

	ret = recv_control_msg(pdev,
		GET_STATUS_CTL, READ_SHUTTER_FORMATTER, &buf, sizeof(buf));
	if (ret < 0)
		return ret;
	*value = buf[0] + (buf[1] << 8);
	if (DEVICE_USE_CODEC2(pdev->type)) {
		/* speed ranges from 0x0 to 0x290 (656) */
		*value *= 256/656;
	} else if (DEVICE_USE_CODEC3(pdev->type)) {
		/* speed seems to range from 0x0 to 0xff */
	}
	return 0;
}