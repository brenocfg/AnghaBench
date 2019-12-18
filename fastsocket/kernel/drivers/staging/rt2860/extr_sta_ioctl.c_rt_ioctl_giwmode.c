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
struct net_device {int /*<<< orphan*/  ml_priv; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  PRTMP_ADAPTER ;

/* Variables and functions */
 scalar_t__ ADHOC_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INFRA_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_AUTO ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  IW_MODE_MONITOR ; 
 scalar_t__ MONITOR_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 

int rt_ioctl_giwmode(struct net_device *dev,
		   struct iw_request_info *info,
		   __u32 *mode, char *extra)
{
	PRTMP_ADAPTER pAdapter = dev->ml_priv;

	if (ADHOC_ON(pAdapter))
		*mode = IW_MODE_ADHOC;
    else if (INFRA_ON(pAdapter))
		*mode = IW_MODE_INFRA;
    else if (MONITOR_ON(pAdapter))
    {
        *mode = IW_MODE_MONITOR;
    }
    else
        *mode = IW_MODE_AUTO;

	DBGPRINT(RT_DEBUG_TRACE, ("==>rt_ioctl_giwmode(mode=%d)\n", *mode));
	return 0;
}