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
 int /*<<< orphan*/  GET_CHROM_CTL ; 
 int /*<<< orphan*/  WB_MODE_FORMATTER ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

int pwc_get_awb(struct pwc_device *pdev)
{
	unsigned char buf;
	int ret;

	ret = recv_control_msg(pdev,
		GET_CHROM_CTL, WB_MODE_FORMATTER, &buf, sizeof(buf));

	if (ret < 0)
		return ret;
	return buf;
}