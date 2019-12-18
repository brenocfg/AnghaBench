#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; void* sa_family; } ;
struct net_device {TYPE_4__* ml_priv; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  Bssid; } ;
struct TYPE_8__ {scalar_t__ WpaSupplicantUP; } ;
struct TYPE_7__ {int /*<<< orphan*/  Bssid; } ;
struct TYPE_10__ {TYPE_3__ MlmeAux; TYPE_2__ StaCfg; TYPE_1__ CommonCfg; } ;
typedef  TYPE_4__* PRTMP_ADAPTER ;

/* Variables and functions */
 scalar_t__ ADHOC_ON (TYPE_4__*) ; 
 void* ARPHRD_ETHER ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ INFRA_ON (TYPE_4__*) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 scalar_t__ WPA_SUPPLICANT_DISABLE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rt_ioctl_giwap(struct net_device *dev,
		      struct iw_request_info *info,
		      struct sockaddr *ap_addr, char *extra)
{
	PRTMP_ADAPTER pAdapter = dev->ml_priv;

	if (INFRA_ON(pAdapter) || ADHOC_ON(pAdapter))
	{
		ap_addr->sa_family = ARPHRD_ETHER;
		memcpy(ap_addr->sa_data, &pAdapter->CommonCfg.Bssid, ETH_ALEN);
	}
    // Add for RT2870
    else if (pAdapter->StaCfg.WpaSupplicantUP != WPA_SUPPLICANT_DISABLE)
    {
        ap_addr->sa_family = ARPHRD_ETHER;
        memcpy(ap_addr->sa_data, &pAdapter->MlmeAux.Bssid, ETH_ALEN);
    }
	else
	{
		DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::SIOCGIWAP(=EMPTY)\n"));
		return -ENOTCONN;
	}

	return 0;
}