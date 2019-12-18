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
struct iw_param {int value; int disabled; int fixed; } ;
struct TYPE_10__ {int data; int /*<<< orphan*/  did; } ;
struct TYPE_8__ {TYPE_3__ data; } ;
struct TYPE_9__ {TYPE_1__ mibattribute; int /*<<< orphan*/  msgcode; } ;
typedef  TYPE_2__ p80211msg_dot11req_mibset_t ;
typedef  TYPE_3__ p80211item_uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/ * ml_priv; } ;
typedef  TYPE_4__ netdevice_t ;
typedef  int /*<<< orphan*/  mibitem ;

/* Variables and functions */
 int /*<<< orphan*/  DIDmib_dot11mac_dot11OperationTable_dot11FragmentationThreshold ; 
 int /*<<< orphan*/  DIDmsg_dot11req_mibget ; 
 int EFAULT ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int p80211req_dorequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p80211wext_giwfrag(netdevice_t *dev,
			      struct iw_request_info *info,
			      struct iw_param *frag, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;
	p80211item_uint32_t mibitem;
	p80211msg_dot11req_mibset_t msg;
	int result;
	int err = 0;

	msg.msgcode = DIDmsg_dot11req_mibget;
	mibitem.did =
	    DIDmib_dot11mac_dot11OperationTable_dot11FragmentationThreshold;
	memcpy(&msg.mibattribute.data, &mibitem, sizeof(mibitem));
	result = p80211req_dorequest(wlandev, (u8 *) & msg);

	if (result) {
		err = -EFAULT;
		goto exit;
	}

	memcpy(&mibitem, &msg.mibattribute.data, sizeof(mibitem));

	frag->value = mibitem.data;
	frag->disabled = (frag->value == 2346);
	frag->fixed = 1;

exit:
	return err;
}