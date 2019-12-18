#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iw_param {int flags; int value; } ;
union iwreq_data {struct iw_param param; } ;
struct net_device {TYPE_2__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  AuthMode; int /*<<< orphan*/  WepStatus; } ;
struct TYPE_5__ {TYPE_1__ StaCfg; } ;
typedef  TYPE_2__* PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int ENETDOWN ; 
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 130 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
 int IW_AUTH_ALG_SHARED_KEY ; 
#define  IW_AUTH_DROP_UNENCRYPTED 129 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_WPA_ENABLED 128 
 int /*<<< orphan*/  Ndis802_11AuthModeShared ; 
 int /*<<< orphan*/  Ndis802_11AuthModeWPA ; 
 int /*<<< orphan*/  Ndis802_11WEPDisabled ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 

int rt_ioctl_giwauth(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	PRTMP_ADAPTER   pAdapter = dev->ml_priv;
	struct iw_param *param = &wrqu->param;

    //check if the interface is down
	if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
  		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
    	return -ENETDOWN;
    }

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_DROP_UNENCRYPTED:
        param->value = (pAdapter->StaCfg.WepStatus == Ndis802_11WEPDisabled) ? 0 : 1;
		break;

	case IW_AUTH_80211_AUTH_ALG:
        param->value = (pAdapter->StaCfg.AuthMode == Ndis802_11AuthModeShared) ? IW_AUTH_ALG_SHARED_KEY : IW_AUTH_ALG_OPEN_SYSTEM;
		break;

	case IW_AUTH_WPA_ENABLED:
		param->value = (pAdapter->StaCfg.AuthMode >= Ndis802_11AuthModeWPA) ? 1 : 0;
		break;

	default:
		return -EOPNOTSUPP;
	}
    DBGPRINT(RT_DEBUG_TRACE, ("rt_ioctl_giwauth::param->value = %d!\n", param->value));
	return 0;
}