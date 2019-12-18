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
 int /*<<< orphan*/  SET_CHROM_CTL ; 
 int /*<<< orphan*/  WB_MODE_FORMATTER ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int pwc_set_awb(struct pwc_device *pdev, int mode)
{
	char buf;
	int ret;

	if (mode < 0)
	    mode = 0;

	if (mode > 4)
	    mode = 4;

	buf = mode & 0x07; /* just the lowest three bits */

	ret = send_control_msg(pdev,
		SET_CHROM_CTL, WB_MODE_FORMATTER, &buf, sizeof(buf));

	if (ret < 0)
		return ret;
	return 0;
}