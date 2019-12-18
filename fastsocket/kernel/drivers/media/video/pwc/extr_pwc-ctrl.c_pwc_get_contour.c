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
 int /*<<< orphan*/  GET_LUM_CTL ; 
 int /*<<< orphan*/  PRESET_CONTOUR_FORMATTER ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

int pwc_get_contour(struct pwc_device *pdev, int *contour)
{
	unsigned char buf;
	int ret;

	ret = recv_control_msg(pdev,
		GET_LUM_CTL, AUTO_CONTOUR_FORMATTER, &buf, sizeof(buf));
	if (ret < 0)
		return ret;

	if (buf == 0) {
		/* auto mode off, query current preset value */
		ret = recv_control_msg(pdev,
			GET_LUM_CTL, PRESET_CONTOUR_FORMATTER,
			&buf, sizeof(buf));
		if (ret < 0)
			return ret;
		*contour = buf << 10;
	}
	else
		*contour = -1;
	return 0;
}