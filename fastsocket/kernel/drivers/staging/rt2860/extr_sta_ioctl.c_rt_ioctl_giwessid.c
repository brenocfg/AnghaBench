#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_3__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;
struct TYPE_7__ {int /*<<< orphan*/  SsidLen; int /*<<< orphan*/  Ssid; } ;
struct TYPE_6__ {scalar_t__ WpaSupplicantUP; } ;
struct TYPE_8__ {TYPE_2__ CommonCfg; TYPE_1__ StaCfg; } ;
typedef  TYPE_3__* PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MONITOR_ON (TYPE_3__*) ; 
 scalar_t__ OPSTATUS_TEST_FLAG (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 scalar_t__ WPA_SUPPLICANT_DISABLE ; 
 int /*<<< orphan*/  fOP_STATUS_MEDIA_STATE_CONNECTED ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rt_ioctl_giwessid(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *data, char *essid)
{
	PRTMP_ADAPTER pAdapter = dev->ml_priv;

	data->flags = 1;
    if (MONITOR_ON(pAdapter))
    {
        data->length  = 0;
        return 0;
    }

	if (OPSTATUS_TEST_FLAG(pAdapter, fOP_STATUS_MEDIA_STATE_CONNECTED))
	{
		DBGPRINT(RT_DEBUG_TRACE ,("MediaState is connected\n"));
		data->length = pAdapter->CommonCfg.SsidLen;
		memcpy(essid, pAdapter->CommonCfg.Ssid, pAdapter->CommonCfg.SsidLen);
	}
#ifdef RT2870
    // Add for RT2870
    else if (pAdapter->StaCfg.WpaSupplicantUP != WPA_SUPPLICANT_DISABLE)
    {
        data->length = pAdapter->CommonCfg.SsidLen;
		memcpy(essid, pAdapter->CommonCfg.Ssid, pAdapter->CommonCfg.SsidLen);
	}
#endif // RT2870 //
	else
	{//the ANY ssid was specified
		data->length  = 0;
		DBGPRINT(RT_DEBUG_TRACE ,("MediaState is not connected, ess\n"));
	}

	return 0;

}