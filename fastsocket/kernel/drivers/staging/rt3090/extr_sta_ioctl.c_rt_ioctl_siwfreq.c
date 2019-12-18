#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {int e; int m; } ;
struct TYPE_6__ {int Channel; } ;
struct TYPE_7__ {TYPE_1__ CommonCfg; } ;
typedef  TYPE_2__* PRTMP_ADAPTER ;

/* Variables and functions */
 scalar_t__ ChannelSanity (TYPE_2__*,int) ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  MAP_KHZ_TO_CHANNEL_ID (int,int) ; 
 TYPE_2__* RTMP_OS_NETDEV_GET_PRIV (struct net_device*) ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_ERROR ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  SIOCSIWFREQ ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 

int rt_ioctl_siwfreq(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_freq *freq, char *extra)
{
	PRTMP_ADAPTER pAdapter = RTMP_OS_NETDEV_GET_PRIV(dev);
	int	chan = -1;

    //check if the interface is down
    if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
        DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        return -ENETDOWN;
    }


	if (freq->e > 1)
		return -EINVAL;

	if((freq->e == 0) && (freq->m <= 1000))
		chan = freq->m;	// Setting by channel number
	else
		MAP_KHZ_TO_CHANNEL_ID( (freq->m /100) , chan); // Setting by frequency - search the table , like 2.412G, 2.422G,

    if (ChannelSanity(pAdapter, chan) == TRUE)
    {
	pAdapter->CommonCfg.Channel = chan;
	DBGPRINT(RT_DEBUG_ERROR, ("==>rt_ioctl_siwfreq::SIOCSIWFREQ[cmd=0x%x] (Channel=%d)\n", SIOCSIWFREQ, pAdapter->CommonCfg.Channel));
    }
    else
        return -EINVAL;

	return 0;
}