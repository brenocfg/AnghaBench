#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; scalar_t__ disabled; } ;
struct TYPE_5__ {int FragmentThreshold; } ;
struct TYPE_6__ {TYPE_1__ CommonCfg; } ;
typedef  TYPE_2__* PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int MAX_FRAG_THRESHOLD ; 
 int MIN_FRAG_THRESHOLD ; 
 TYPE_2__* RTMP_OS_NETDEV_GET_PRIV (struct net_device*) ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int __cpu_to_le16 (int) ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 

int rt_ioctl_siwfrag(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_param *frag, char *extra)
{
	PRTMP_ADAPTER pAdapter = RTMP_OS_NETDEV_GET_PRIV(dev);
	u16 val;

	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
		return -ENETDOWN;
	}

	if (frag->disabled)
		val = MAX_FRAG_THRESHOLD;
	else if (frag->value >= MIN_FRAG_THRESHOLD || frag->value <= MAX_FRAG_THRESHOLD)
        val = __cpu_to_le16(frag->value & ~0x1); /* even numbers only */
	else if (frag->value == 0)
	    val = MAX_FRAG_THRESHOLD;
	else
		return -EINVAL;

	pAdapter->CommonCfg.FragmentThreshold = val;
	return 0;
}