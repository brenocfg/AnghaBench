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
 int /*<<< orphan*/  AWB_CONTROL_SPEED_FORMATTER ; 
 int /*<<< orphan*/  GET_CHROM_CTL ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int pwc_get_wb_speed(struct pwc_device *pdev, int *value)
{
	unsigned char buf;
	int ret;

	ret = recv_control_msg(pdev,
		GET_CHROM_CTL, AWB_CONTROL_SPEED_FORMATTER, &buf, sizeof(buf));
	if (ret < 0)
		return ret;
	*value = buf * 0x7f0;
	return 0;
}