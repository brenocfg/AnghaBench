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
typedef  int /*<<< orphan*/  u8 ;
struct tcw {int dummy; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int) ; 
 int ccw_device_tm_start_key (struct ccw_device*,struct tcw*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ccw_device_tm_start_timeout_key(struct ccw_device *cdev, struct tcw *tcw,
				    unsigned long intparm, u8 lpm, u8 key,
				    int expires)
{
	int ret;

	ccw_device_set_timeout(cdev, expires);
	ret = ccw_device_tm_start_key(cdev, tcw, intparm, lpm, key);
	if (ret != 0)
		ccw_device_set_timeout(cdev, 0);
	return ret;
}