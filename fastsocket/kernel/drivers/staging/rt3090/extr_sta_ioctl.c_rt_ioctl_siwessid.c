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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ length; scalar_t__ flags; } ;
typedef  char* PSTRING ;
typedef  int /*<<< orphan*/  PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 scalar_t__ FALSE ; 
 scalar_t__ IW_ESSID_MAX_SIZE ; 
 scalar_t__ MAX_LEN_OF_SSID ; 
 int /*<<< orphan*/  MEM_ALLOC_FLAG ; 
 int /*<<< orphan*/  NdisMoveMemory (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  NdisZeroMemory (char*,scalar_t__) ; 
 int /*<<< orphan*/  RTMP_OS_NETDEV_GET_PRIV (struct net_device*) ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 scalar_t__ Set_SSID_Proc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

int rt_ioctl_siwessid(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *data, char *essid)
{
	PRTMP_ADAPTER pAdapter = RTMP_OS_NETDEV_GET_PRIV(dev);

	//check if the interface is down
    if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
	return -ENETDOWN;
    }

	if (data->flags)
	{
		PSTRING	pSsidString = NULL;

		// Includes null character.
		if (data->length > (IW_ESSID_MAX_SIZE + 1))
			return -E2BIG;

		pSsidString = kmalloc(MAX_LEN_OF_SSID+1, MEM_ALLOC_FLAG);
		if (pSsidString)
        {
			NdisZeroMemory(pSsidString, MAX_LEN_OF_SSID+1);
			NdisMoveMemory(pSsidString, essid, data->length);
			if (Set_SSID_Proc(pAdapter, pSsidString) == FALSE)
				return -EINVAL;
		}
		else
			return -ENOMEM;
		}
	else
    {
		// ANY ssid
		if (Set_SSID_Proc(pAdapter, "") == FALSE)
			return -EINVAL;
    }
	return 0;
}