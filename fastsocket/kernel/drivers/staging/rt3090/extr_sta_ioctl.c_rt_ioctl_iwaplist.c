#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {char* sa_data; int /*<<< orphan*/  sa_family; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_quality {char* sa_data; int /*<<< orphan*/  sa_family; } ;
struct iw_point {int length; int flags; } ;
typedef  int /*<<< orphan*/  qual ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_8__ {int BssNr; TYPE_1__* BssEntry; } ;
struct TYPE_9__ {TYPE_2__ ScanTab; } ;
struct TYPE_7__ {int /*<<< orphan*/  Rssi; struct sockaddr* Bssid; } ;
typedef  TYPE_3__* PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int IW_MAX_AP ; 
 int MAC_ADDR_LEN ; 
 TYPE_3__* RTMP_OS_NETDEV_GET_PRIV (struct net_device*) ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 
 int /*<<< orphan*/  memcpy (char*,struct sockaddr**,int) ; 
 int /*<<< orphan*/  set_quality (TYPE_3__*,struct sockaddr*,int /*<<< orphan*/ ) ; 

int rt_ioctl_iwaplist(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_point *data, char *extra)
{
	PRTMP_ADAPTER pAdapter = RTMP_OS_NETDEV_GET_PRIV(dev);

	struct sockaddr addr[IW_MAX_AP];
	struct iw_quality qual[IW_MAX_AP];
	int i;

	//check if the interface is down
    if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
		data->length = 0;
		return 0;
        //return -ENETDOWN;
	}

	for (i = 0; i <IW_MAX_AP ; i++)
	{
		if (i >=  pAdapter->ScanTab.BssNr)
			break;
		addr[i].sa_family = ARPHRD_ETHER;
			memcpy(addr[i].sa_data, &pAdapter->ScanTab.BssEntry[i].Bssid, MAC_ADDR_LEN);
		set_quality(pAdapter, &qual[i], pAdapter->ScanTab.BssEntry[i].Rssi);
	}
	data->length = i;
	memcpy(extra, &addr, i*sizeof(addr[0]));
	data->flags = 1;		/* signal quality present (sort of) */
	memcpy(extra + i*sizeof(addr[0]), &qual, i*sizeof(qual[i]));

	return 0;
}