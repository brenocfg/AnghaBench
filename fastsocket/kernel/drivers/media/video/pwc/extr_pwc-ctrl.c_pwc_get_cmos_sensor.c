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
 int /*<<< orphan*/  GET_STATUS_CTL ; 
 int SENSOR_TYPE_FORMATTER1 ; 
 int SENSOR_TYPE_FORMATTER2 ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int,unsigned char*,int) ; 

int pwc_get_cmos_sensor(struct pwc_device *pdev, int *sensor)
{
	unsigned char buf;
	int ret = -1, request;

	if (pdev->type < 675)
		request = SENSOR_TYPE_FORMATTER1;
	else if (pdev->type < 730)
		return -1; /* The Vesta series doesn't have this call */
	else
		request = SENSOR_TYPE_FORMATTER2;

	ret = recv_control_msg(pdev,
		GET_STATUS_CTL, request, &buf, sizeof(buf));
	if (ret < 0)
		return ret;
	if (pdev->type < 675)
		*sensor = buf | 0x100;
	else
		*sensor = buf;
	return 0;
}