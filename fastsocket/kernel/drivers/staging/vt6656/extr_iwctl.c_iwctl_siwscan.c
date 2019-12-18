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
typedef  int /*<<< orphan*/  wrqu ;
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_scan_req {int essid_len; scalar_t__ scan_type; int /*<<< orphan*/  essid; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; int flags; } ;
struct TYPE_5__ {scalar_t__ eScanState; void* eScanType; } ;
struct TYPE_6__ {int flags; scalar_t__ byReAssocCount; int /*<<< orphan*/  lock; int /*<<< orphan*/  bLinkPass; int /*<<< orphan*/  dev; TYPE_2__ sMgmtObj; } ;
struct TYPE_4__ {char* abySSID; int len; int /*<<< orphan*/  byElementID; } ;
typedef  TYPE_1__* PWLAN_IE_SSID ;
typedef  TYPE_2__* PSMgmtObject ;
typedef  TYPE_3__* PSDevice ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  union iwreq_data BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BSSvClearBSSList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DEVICE_FLAGS_OPENED ; 
 int EAGAIN ; 
 int EINVAL ; 
 int IW_SCAN_THIS_ESSID ; 
 scalar_t__ IW_SCAN_TYPE_PASSIVE ; 
 int /*<<< orphan*/  PRINT_K (char*,...) ; 
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  WLAN_CMD_BSSID_SCAN ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int WLAN_IEHDR_LEN ; 
 int WLAN_SSID_MAXLEN ; 
 scalar_t__ WMAC_IS_SCANNING ; 
 void* WMAC_SCAN_ACTIVE ; 
 void* WMAC_SCAN_PASSIVE ; 
 int /*<<< orphan*/  bScheduleCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

int iwctl_siwscan(struct net_device *dev,
             struct iw_request_info *info,
			 struct iw_point *wrq,
             char *extra)
{
	PSDevice	        pDevice = (PSDevice)netdev_priv(dev);
	 PSMgmtObject        pMgmt = &(pDevice->sMgmtObj);
	struct iw_scan_req  *req = (struct iw_scan_req *)extra;
	BYTE                abyScanSSID[WLAN_IEHDR_LEN + WLAN_SSID_MAXLEN + 1];
	PWLAN_IE_SSID       pItemSSID=NULL;

//2008-0920-01<Add>by MikeLiu
  if (!(pDevice->flags & DEVICE_FLAGS_OPENED))
        return -EINVAL;

    PRINT_K(" SIOCSIWSCAN \n");

if (pMgmt->eScanState ==  WMAC_IS_SCANNING) {
        // In scanning..
     PRINT_K("SIOCSIWSCAN(overlap??)-->In scanning...\n");
     return -EAGAIN;
  }

if(pDevice->byReAssocCount > 0) {   //reject scan when re-associating!
//send scan event to wpa_Supplicant
  union iwreq_data wrqu;
 PRINT_K("wireless_send_event--->SIOCGIWSCAN(scan done)\n");
 memset(&wrqu, 0, sizeof(wrqu));
 wireless_send_event(pDevice->dev, SIOCGIWSCAN, &wrqu, NULL);
  return 0;
}

	spin_lock_irq(&pDevice->lock);

   #ifdef update_BssList
        BSSvClearBSSList((HANDLE)pDevice, pDevice->bLinkPass);
   #endif

//mike add: active scan OR passive scan OR desire_ssid scan
 if(wrq->length == sizeof(struct iw_scan_req)) {
   if (wrq->flags & IW_SCAN_THIS_ESSID)  {                               //desire_ssid scan
       memset(abyScanSSID, 0, WLAN_IEHDR_LEN + WLAN_SSID_MAXLEN + 1);
       pItemSSID = (PWLAN_IE_SSID)abyScanSSID;
       pItemSSID->byElementID = WLAN_EID_SSID;
       memcpy(pItemSSID->abySSID, req->essid, (int)req->essid_len);
         if (pItemSSID->abySSID[req->essid_len - 1] == '\0') {
           if(req->essid_len>0)
		pItemSSID->len = req->essid_len - 1;
         }
	else
	  pItemSSID->len = req->essid_len;
	  pMgmt->eScanType = WMAC_SCAN_PASSIVE;
         PRINT_K("SIOCSIWSCAN:[desired_ssid=%s,len=%d]\n",((PWLAN_IE_SSID)abyScanSSID)->abySSID,
		 	                                                                                ((PWLAN_IE_SSID)abyScanSSID)->len);
	bScheduleCommand((HANDLE) pDevice, WLAN_CMD_BSSID_SCAN, abyScanSSID);
	spin_unlock_irq(&pDevice->lock);

	return 0;
   }
   else if(req->scan_type == IW_SCAN_TYPE_PASSIVE) {          //passive scan
       pMgmt->eScanType = WMAC_SCAN_PASSIVE;
   }
 }
 else {           //active scan
     pMgmt->eScanType = WMAC_SCAN_ACTIVE;
 }

	 pMgmt->eScanType = WMAC_SCAN_PASSIVE;
         //printk("SIOCSIWSCAN:WLAN_CMD_BSSID_SCAN\n");
	bScheduleCommand((HANDLE) pDevice, WLAN_CMD_BSSID_SCAN, NULL);
	spin_unlock_irq(&pDevice->lock);

	return 0;
}