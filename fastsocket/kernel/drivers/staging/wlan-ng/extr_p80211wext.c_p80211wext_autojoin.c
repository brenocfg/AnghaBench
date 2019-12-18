#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int hostwep; int /*<<< orphan*/  netdev; } ;
typedef  TYPE_4__ wlandevice_t ;
typedef  int /*<<< orphan*/  u8 ;
struct iw_point {int length; } ;
struct TYPE_9__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_2__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_3__ ssid; int /*<<< orphan*/  msgcode; TYPE_1__ authtype; } ;
typedef  TYPE_5__ p80211msg_lnxreq_autojoin_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIDmsg_lnxreq_autojoin ; 
 int EFAULT ; 
 int HOSTWEP_SHAREDKEY ; 
 int IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  P80211ENUM_authalg_opensystem ; 
 int /*<<< orphan*/  P80211ENUM_authalg_sharedkey ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int p80211req_dorequest (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int p80211wext_giwessid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct iw_point*,char*) ; 

__attribute__((used)) static int p80211wext_autojoin(wlandevice_t *wlandev)
{
	p80211msg_lnxreq_autojoin_t msg;
	struct iw_point data;
	char ssid[IW_ESSID_MAX_SIZE];

	int result;
	int err = 0;

	/* Get ESSID */
	result = p80211wext_giwessid(wlandev->netdev, NULL, &data, ssid);

	if (result) {
		err = -EFAULT;
		goto exit;
	}

	if (wlandev->hostwep & HOSTWEP_SHAREDKEY)
		msg.authtype.data = P80211ENUM_authalg_sharedkey;
	else
		msg.authtype.data = P80211ENUM_authalg_opensystem;

	msg.msgcode = DIDmsg_lnxreq_autojoin;

	/* Trim the last '\0' to fit the SSID format */

	if (data.length && ssid[data.length - 1] == '\0')
		data.length = data.length - 1;

	memcpy(msg.ssid.data.data, ssid, data.length);
	msg.ssid.data.len = data.length;

	result = p80211req_dorequest(wlandev, (u8 *) & msg);

	if (result) {
		err = -EFAULT;
		goto exit;
	}

exit:

	return err;

}