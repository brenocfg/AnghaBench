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
struct pwc_mpt_status {unsigned char status; unsigned char time_pan; unsigned char time_tilt; } ;
struct pwc_device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MPT_CTL ; 
 int /*<<< orphan*/  PT_STATUS_FORMATTER ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**,int) ; 

__attribute__((used)) static int pwc_mpt_get_status(struct pwc_device *pdev, struct pwc_mpt_status *status)
{
	int ret;
	unsigned char buf[5];

	ret = recv_control_msg(pdev,
		GET_MPT_CTL, PT_STATUS_FORMATTER, &buf, sizeof(buf));
	if (ret < 0)
		return ret;
	status->status = buf[0] & 0x7; // 3 bits are used for reporting
	status->time_pan = (buf[1] << 8) + buf[2];
	status->time_tilt = (buf[3] << 8) + buf[4];
	return 0;
}