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
struct pwc_device {int type; int release; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  SET_POWER_SAVE_MODE_FORMATTER ; 
 int /*<<< orphan*/  SET_STATUS_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int pwc_camera_power(struct pwc_device *pdev, int power)
{
	char buf;

	if (pdev->type < 675 || (pdev->type < 730 && pdev->release < 6))
		return 0;	/* Not supported by Nala or Timon < release 6 */

	if (power)
		buf = 0x00; /* active */
	else
		buf = 0xFF; /* power save */
	return send_control_msg(pdev,
		SET_STATUS_CTL, SET_POWER_SAVE_MODE_FORMATTER,
		&buf, sizeof(buf));
}