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
 int /*<<< orphan*/  PT_RELATIVE_CONTROL_FORMATTER ; 
 int /*<<< orphan*/  SET_MPT_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**,int) ; 

__attribute__((used)) static int _pwc_mpt_set_angle(struct pwc_device *pdev, int pan, int tilt)
{
	unsigned char buf[4];

	/* set new relative angle; angles are expressed in degrees * 100,
	   but cam as .5 degree resolution, hence divide by 200. Also
	   the angle must be multiplied by 64 before it's send to
	   the cam (??)
	 */
	pan  =  64 * pan  / 100;
	tilt = -64 * tilt / 100; /* positive tilt is down, which is not what the user would expect */
	buf[0] = pan & 0xFF;
	buf[1] = (pan >> 8) & 0xFF;
	buf[2] = tilt & 0xFF;
	buf[3] = (tilt >> 8) & 0xFF;
	return send_control_msg(pdev,
		SET_MPT_CTL, PT_RELATIVE_CONTROL_FORMATTER, &buf, sizeof(buf));
}