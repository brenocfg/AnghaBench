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
struct pwc_device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AGC_MODE_FORMATTER ; 
 int /*<<< orphan*/  PRESET_AGC_FORMATTER ; 
 int /*<<< orphan*/  SET_LUM_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int pwc_set_agc(struct pwc_device *pdev, int mode, int value)
{
	char buf;
	int ret;

	if (mode)
		buf = 0x0; /* auto */
	else
		buf = 0xff; /* fixed */

	ret = send_control_msg(pdev,
		SET_LUM_CTL, AGC_MODE_FORMATTER, &buf, sizeof(buf));

	if (!mode && ret >= 0) {
		if (value < 0)
			value = 0;
		if (value > 0xffff)
			value = 0xffff;
		buf = (value >> 10) & 0x3F;
		ret = send_control_msg(pdev,
			SET_LUM_CTL, PRESET_AGC_FORMATTER, &buf, sizeof(buf));
	}
	if (ret < 0)
		return ret;
	return 0;
}