#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa_data; } ;
struct iw_mlme {int cmd; TYPE_1__ addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  abyDesireBSSID; int /*<<< orphan*/  abyCurrBSSID; } ;
struct TYPE_6__ {int /*<<< orphan*/  PortOffset; int /*<<< orphan*/  sKey; int /*<<< orphan*/  bLinkPass; TYPE_2__ sMgmtObj; } ;
typedef  TYPE_2__* PSMgmtObject ;
typedef  TYPE_3__* PSDevice ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
#define  IW_MLME_DEAUTH 129 
#define  IW_MLME_DISASSOC 128 
 int /*<<< orphan*/  KeyvInitTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WLAN_CMD_DISASSOCIATE ; 
 int /*<<< orphan*/  bScheduleCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 

int iwctl_siwmlme(struct net_device *dev,
				struct iw_request_info * info,
				struct iw_point *wrq,
				char *extra)
{
	PSDevice			pDevice = (PSDevice)netdev_priv(dev);
	PSMgmtObject	pMgmt = &(pDevice->sMgmtObj);
	struct iw_mlme *mlme = (struct iw_mlme *)extra;
	//u16 reason = cpu_to_le16(mlme->reason_code);
	int ret = 0;

	if(memcmp(pMgmt->abyCurrBSSID, mlme->addr.sa_data, ETH_ALEN)){
		ret = -EINVAL;
		return ret;
	}
	switch(mlme->cmd){
	case IW_MLME_DEAUTH:
		//this command seems to be not complete,please test it --einsnliu
		//bScheduleCommand((HANDLE) pDevice, WLAN_CMD_DEAUTH, (PBYTE)&reason);
		break;
	case IW_MLME_DISASSOC:
		if(pDevice->bLinkPass == TRUE){
					  printk("iwctl_siwmlme--->send DISASSOCIATE\n");
		  //clear related flags
		   memset(pMgmt->abyDesireBSSID, 0xFF,6);
		KeyvInitTable(&pDevice->sKey, pDevice->PortOffset);
			bScheduleCommand((HANDLE)pDevice, WLAN_CMD_DISASSOCIATE, NULL);
		}
		break;
	default:
		ret = -EOPNOTSUPP;
	}

	return ret;

}