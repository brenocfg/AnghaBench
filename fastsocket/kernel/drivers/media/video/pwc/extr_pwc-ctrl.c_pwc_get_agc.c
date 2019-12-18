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
 int /*<<< orphan*/  GET_LUM_CTL ; 
 int /*<<< orphan*/  GET_STATUS_CTL ; 
 int /*<<< orphan*/  PRESET_AGC_FORMATTER ; 
 int /*<<< orphan*/  READ_AGC_FORMATTER ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

int pwc_get_agc(struct pwc_device *pdev, int *value)
{
	unsigned char buf;
	int ret;

	ret = recv_control_msg(pdev,
		GET_LUM_CTL, AGC_MODE_FORMATTER, &buf, sizeof(buf));
	if (ret < 0)
		return ret;

	if (buf != 0) { /* fixed */
		ret = recv_control_msg(pdev,
			GET_LUM_CTL, PRESET_AGC_FORMATTER, &buf, sizeof(buf));
		if (ret < 0)
			return ret;
		if (buf > 0x3F)
			buf = 0x3F;
		*value = (buf << 10);
	}
	else { /* auto */
		ret = recv_control_msg(pdev,
			GET_STATUS_CTL, READ_AGC_FORMATTER, &buf, sizeof(buf));
		if (ret < 0)
			return ret;
		/* Gah... this value ranges from 0x00 ... 0x9F */
		if (buf > 0x9F)
			buf = 0x9F;
		*value = -(48 + buf * 409);
	}

	return 0;
}