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
 int /*<<< orphan*/  DYNAMIC_NOISE_CONTROL_FORMATTER ; 
 int /*<<< orphan*/  GET_LUM_CTL ; 
 int recv_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

int pwc_get_dynamic_noise(struct pwc_device *pdev, int *noise)
{
	int ret;
	unsigned char buf;

	ret = recv_control_msg(pdev,
		GET_LUM_CTL, DYNAMIC_NOISE_CONTROL_FORMATTER,
		&buf, sizeof(buf));
	if (ret < 0)
		return ret;
	*noise = buf;
	return 0;
}