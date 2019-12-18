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
 int /*<<< orphan*/  BACK_LIGHT_COMPENSATION_FORMATTER ; 
 int /*<<< orphan*/  SET_LUM_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

int pwc_set_backlight(struct pwc_device *pdev, int backlight)
{
	unsigned char buf;

	if (backlight)
		buf = 0xff;
	else
		buf = 0x0;
	return send_control_msg(pdev,
		SET_LUM_CTL, BACK_LIGHT_COMPENSATION_FORMATTER,
		&buf, sizeof(buf));
}