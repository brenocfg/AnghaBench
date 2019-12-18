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
 int EINVAL ; 
 int SATURATION_MODE_FORMATTER1 ; 
 int SATURATION_MODE_FORMATTER2 ; 
 int /*<<< orphan*/  SET_CHROM_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int,char*,int) ; 

int pwc_set_saturation(struct pwc_device *pdev, int value)
{
	char buf;
	int saturation_register;

	if (pdev->type < 675)
		return -EINVAL;
	if (value < -100)
		value = -100;
	if (value > 100)
		value = 100;
	if (pdev->type < 730)
		saturation_register = SATURATION_MODE_FORMATTER2;
	else
		saturation_register = SATURATION_MODE_FORMATTER1;
	return send_control_msg(pdev,
		SET_CHROM_CTL, saturation_register, &buf, sizeof(buf));
}