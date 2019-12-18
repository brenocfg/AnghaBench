#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wlandevice_t ;
typedef  int /*<<< orphan*/  u8 ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; scalar_t__ flags; } ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {int data; } ;
struct TYPE_10__ {TYPE_2__ resultcode; TYPE_1__ bssindex; int /*<<< orphan*/  msgcode; } ;
typedef  TYPE_3__ p80211msg_dot11req_scan_results_t ;
struct TYPE_11__ {int /*<<< orphan*/ * ml_priv; } ;
typedef  TYPE_4__ netdevice_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DIDmsg_dot11req_scan_results ; 
 int IW_MAX_AP ; 
 int IW_SCAN_MAX_DATA ; 
 scalar_t__ P80211ENUM_resultcode_success ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int p80211req_dorequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int prism2_result2err (scalar_t__) ; 
 char* wext_translate_bss (struct iw_request_info*,char*,char*,TYPE_3__*) ; 

__attribute__((used)) static int p80211wext_giwscan(netdevice_t *dev,
			      struct iw_request_info *info,
			      struct iw_point *srq, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;
	p80211msg_dot11req_scan_results_t msg;
	int result = 0;
	int err = 0;
	int i = 0;
	int scan_good = 0;
	char *current_ev = extra;

	/* Since wireless tools doesn't really have a way of passing how
	 * many scan results results there were back here, keep grabbing them
	 * until we fail.
	 */
	do {
		memset(&msg, 0, sizeof(msg));
		msg.msgcode = DIDmsg_dot11req_scan_results;
		msg.bssindex.data = i;

		result = p80211req_dorequest(wlandev, (u8 *) & msg);
		if ((result != 0) ||
		    (msg.resultcode.data != P80211ENUM_resultcode_success)) {
			break;
		}

		current_ev =
		    wext_translate_bss(info, current_ev,
				       extra + IW_SCAN_MAX_DATA, &msg);
		scan_good = 1;
		i++;
	} while (i < IW_MAX_AP);

	srq->length = (current_ev - extra);
	srq->flags = 0;		/* todo */

	if (result && !scan_good)
		err = prism2_result2err(msg.resultcode.data);

	return err;
}