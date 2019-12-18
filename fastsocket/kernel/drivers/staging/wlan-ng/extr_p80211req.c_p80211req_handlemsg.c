#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int hostwep; } ;
typedef  TYPE_3__ wlandevice_t ;
struct TYPE_12__ {int msgcode; } ;
typedef  TYPE_4__ p80211msg_t ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_1__ encrypt; TYPE_2__ decrypt; } ;
typedef  TYPE_5__ p80211msg_lnxreq_hostwep_t ;
typedef  int /*<<< orphan*/  p80211msg_dot11req_mibget_t ;

/* Variables and functions */
#define  DIDmsg_dot11req_mibget 130 
#define  DIDmsg_dot11req_mibset 129 
#define  DIDmsg_lnxreq_hostwep 128 
 int HOSTWEP_DECRYPT ; 
 int HOSTWEP_ENCRYPT ; 
 int /*<<< orphan*/  P80211ENUM_truth_true ; 
 int /*<<< orphan*/  p80211req_mibset_mibget (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void p80211req_handlemsg(wlandevice_t *wlandev, p80211msg_t *msg)
{
	switch (msg->msgcode) {

	case DIDmsg_lnxreq_hostwep:{
			p80211msg_lnxreq_hostwep_t *req =
			    (p80211msg_lnxreq_hostwep_t *) msg;
			wlandev->hostwep &=
			    ~(HOSTWEP_DECRYPT | HOSTWEP_ENCRYPT);
			if (req->decrypt.data == P80211ENUM_truth_true)
				wlandev->hostwep |= HOSTWEP_DECRYPT;
			if (req->encrypt.data == P80211ENUM_truth_true)
				wlandev->hostwep |= HOSTWEP_ENCRYPT;

			break;
		}
	case DIDmsg_dot11req_mibget:
	case DIDmsg_dot11req_mibset:{
			int isget = (msg->msgcode == DIDmsg_dot11req_mibget);
			p80211msg_dot11req_mibget_t *mib_msg =
			    (p80211msg_dot11req_mibget_t *) msg;
			p80211req_mibset_mibget(wlandev, mib_msg, isget);
		}
	default:
		;
	}			/* switch msg->msgcode */

	return;
}