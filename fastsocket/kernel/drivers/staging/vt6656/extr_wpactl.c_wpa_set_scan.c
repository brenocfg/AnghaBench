#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_8__ {TYPE_1__ scan_req; } ;
struct viawget_wpa_param {TYPE_2__ u; } ;
struct TYPE_10__ {scalar_t__ abyDesireSSID; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  bLinkPass; TYPE_4__ sMgmtObj; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  abySSID; int /*<<< orphan*/  byElementID; } ;
typedef  TYPE_3__* PWLAN_IE_SSID ;
typedef  TYPE_4__* PSMgmtObject ;
typedef  TYPE_5__* PSDevice ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  BSSvClearBSSList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_CMD_BSSID_SCAN ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 scalar_t__ WLAN_IEHDR_LEN ; 
 scalar_t__ WLAN_SSID_MAXLEN ; 
 int /*<<< orphan*/  bScheduleCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wpa_set_scan(PSDevice pDevice,
				     struct viawget_wpa_param *param)
{
	int ret = 0;

//2007-0919-01<Add>by MikeLiu
/**set ap_scan=1&&scan_ssid=1 under hidden ssid mode**/
        PSMgmtObject        pMgmt = &(pDevice->sMgmtObj);
        PWLAN_IE_SSID       pItemSSID;
printk("wpa_set_scan-->desired [ssid=%s,ssid_len=%d]\n",
	     param->u.scan_req.ssid,param->u.scan_req.ssid_len);
// Set the SSID
memset(pMgmt->abyDesireSSID, 0, WLAN_IEHDR_LEN + WLAN_SSID_MAXLEN + 1);
pItemSSID = (PWLAN_IE_SSID)pMgmt->abyDesireSSID;
pItemSSID->byElementID = WLAN_EID_SSID;
memcpy(pItemSSID->abySSID, param->u.scan_req.ssid, param->u.scan_req.ssid_len);
pItemSSID->len = param->u.scan_req.ssid_len;

    spin_lock_irq(&pDevice->lock);
    BSSvClearBSSList((HANDLE)pDevice, pDevice->bLinkPass);
  //  bScheduleCommand((HANDLE) pDevice, WLAN_CMD_BSSID_SCAN, NULL);
        bScheduleCommand((HANDLE) pDevice, WLAN_CMD_BSSID_SCAN, pMgmt->abyDesireSSID);
    spin_unlock_irq(&pDevice->lock);

    return ret;
}