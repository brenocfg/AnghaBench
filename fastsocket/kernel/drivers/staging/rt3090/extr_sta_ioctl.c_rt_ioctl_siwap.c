#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {int AutoReconnectSsidLen; int /*<<< orphan*/  CurrReqIsFromNdis; } ;
struct TYPE_9__ {scalar_t__ CurrState; } ;
struct TYPE_10__ {TYPE_1__ CntlMachine; } ;
struct TYPE_12__ {TYPE_3__ MlmeAux; TYPE_2__ Mlme; } ;
typedef  TYPE_4__* PRTMP_ADAPTER ;
typedef  int /*<<< orphan*/ * NDIS_802_11_MAC_ADDRESS ;

/* Variables and functions */
 scalar_t__ CNTL_IDLE ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAC_ADDR_LEN ; 
 int /*<<< orphan*/  MLME_CNTL_STATE_MACHINE ; 
 int /*<<< orphan*/  MlmeEnqueue (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OID_802_11_BSSID ; 
 int /*<<< orphan*/  RTMP_MLME_RESET_STATE_MACHINE (TYPE_4__*) ; 
 TYPE_4__* RTMP_OS_NETDEV_GET_PRIV (struct net_device*) ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rt_ioctl_siwap(struct net_device *dev,
		      struct iw_request_info *info,
		      struct sockaddr *ap_addr, char *extra)
{
	PRTMP_ADAPTER pAdapter = RTMP_OS_NETDEV_GET_PRIV(dev);
    NDIS_802_11_MAC_ADDRESS Bssid;

	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
	return -ENETDOWN;
    }

	if (pAdapter->Mlme.CntlMachine.CurrState != CNTL_IDLE)
    {
        RTMP_MLME_RESET_STATE_MACHINE(pAdapter);
        DBGPRINT(RT_DEBUG_TRACE, ("!!! MLME busy, reset MLME state machine !!!\n"));
    }

    // tell CNTL state machine to call NdisMSetInformationComplete() after completing
    // this request, because this request is initiated by NDIS.
    pAdapter->MlmeAux.CurrReqIsFromNdis = FALSE;
	// Prevent to connect AP again in STAMlmePeriodicExec
	pAdapter->MlmeAux.AutoReconnectSsidLen= 32;

    memset(Bssid, 0, MAC_ADDR_LEN);
    memcpy(Bssid, ap_addr->sa_data, MAC_ADDR_LEN);
    MlmeEnqueue(pAdapter,
                MLME_CNTL_STATE_MACHINE,
                OID_802_11_BSSID,
                sizeof(NDIS_802_11_MAC_ADDRESS),
                (VOID *)&Bssid);

    DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::SIOCSIWAP %02x:%02x:%02x:%02x:%02x:%02x\n",
        Bssid[0], Bssid[1], Bssid[2], Bssid[3], Bssid[4], Bssid[5]));

	return 0;
}