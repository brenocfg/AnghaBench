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
 int /*<<< orphan*/  AUTO_CONTOUR_FORMATTER ; 
 int /*<<< orphan*/  PRESET_CONTOUR_FORMATTER ; 
 int /*<<< orphan*/  SET_LUM_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

int pwc_set_contour(struct pwc_device *pdev, int contour)
{
	unsigned char buf;
	int ret;

	if (contour < 0)
		buf = 0xff; /* auto contour on */
	else
		buf = 0x0; /* auto contour off */
	ret = send_control_msg(pdev,
		SET_LUM_CTL, AUTO_CONTOUR_FORMATTER, &buf, sizeof(buf));
	if (ret < 0)
		return ret;

	if (contour < 0)
		return 0;
	if (contour > 0xffff)
		contour = 0xffff;

	buf = (contour >> 10); /* contour preset is [0..3f] */
	ret = send_control_msg(pdev,
		SET_LUM_CTL, PRESET_CONTOUR_FORMATTER, &buf, sizeof(buf));
	if (ret < 0)
		return ret;
	return 0;
}