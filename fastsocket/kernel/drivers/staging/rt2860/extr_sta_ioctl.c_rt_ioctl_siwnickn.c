#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_1__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ length; } ;
struct TYPE_3__ {int /*<<< orphan*/  nickname; } ;
typedef  TYPE_1__* PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENETDOWN ; 
 scalar_t__ IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int rt_ioctl_siwnickn(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *data, char *nickname)
{
	PRTMP_ADAPTER pAdapter = dev->ml_priv;

    //check if the interface is down
    if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
        DBGPRINT(RT_DEBUG_TRACE ,("INFO::Network is down!\n"));
        return -ENETDOWN;
    }

	if (data->length > IW_ESSID_MAX_SIZE)
		return -EINVAL;

	memset(pAdapter->nickname, 0, IW_ESSID_MAX_SIZE + 1);
	memcpy(pAdapter->nickname, nickname, data->length);


	return 0;
}