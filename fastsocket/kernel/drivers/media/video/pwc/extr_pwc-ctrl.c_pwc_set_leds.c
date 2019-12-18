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
struct pwc_device {int type; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FORMATTER ; 
 int /*<<< orphan*/  SET_STATUS_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**,int) ; 

int pwc_set_leds(struct pwc_device *pdev, int on_value, int off_value)
{
	unsigned char buf[2];

	if (pdev->type < 730)
		return 0;
	on_value /= 100;
	off_value /= 100;
	if (on_value < 0)
		on_value = 0;
	if (on_value > 0xff)
		on_value = 0xff;
	if (off_value < 0)
		off_value = 0;
	if (off_value > 0xff)
		off_value = 0xff;

	buf[0] = on_value;
	buf[1] = off_value;

	return send_control_msg(pdev,
		SET_STATUS_CTL, LED_FORMATTER, &buf, sizeof(buf));
}