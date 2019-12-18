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
 int /*<<< orphan*/  GET_CHROM_CTL ; 
 int SATURATION_MODE_FORMATTER1 ; 
 int SATURATION_MODE_FORMATTER2 ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int,char*,int) ; 

int pwc_get_saturation(struct pwc_device *pdev, int *value)
{
	char buf;
	int ret, saturation_register;

	if (pdev->type < 675)
		return -EINVAL;
	if (pdev->type < 730)
		saturation_register = SATURATION_MODE_FORMATTER2;
	else
		saturation_register = SATURATION_MODE_FORMATTER1;
	ret = recv_control_msg(pdev,
		GET_CHROM_CTL, saturation_register, &buf, sizeof(buf));
	if (ret < 0)
		return ret;
	*value = (signed)buf;
	return 0;
}