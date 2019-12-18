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
typedef  int u16 ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; scalar_t__ disabled; } ;
struct TYPE_10__ {int data; int /*<<< orphan*/  did; } ;
struct TYPE_8__ {TYPE_3__ data; } ;
struct TYPE_9__ {TYPE_1__ mibattribute; int /*<<< orphan*/  msgcode; } ;
typedef  TYPE_2__ p80211msg_dot11req_mibset_t ;
typedef  TYPE_3__ p80211item_uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/ * ml_priv; } ;
typedef  TYPE_4__ netdevice_t ;
typedef  int /*<<< orphan*/  mibitem ;

/* Variables and functions */
 int /*<<< orphan*/  DIDmib_dot11mac_dot11OperationTable_dot11LongRetryLimit ; 
 int /*<<< orphan*/  DIDmib_dot11mac_dot11OperationTable_dot11MaxTransmitMSDULifetime ; 
 int /*<<< orphan*/  DIDmib_dot11mac_dot11OperationTable_dot11ShortRetryLimit ; 
 int /*<<< orphan*/  DIDmsg_dot11req_mibget ; 
 int EFAULT ; 
 int IW_RETRY_LIFETIME ; 
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int IW_RETRY_TYPE ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int p80211req_dorequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p80211wext_giwretry(netdevice_t *dev,
			       struct iw_request_info *info,
			       struct iw_param *rrq, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;
	p80211item_uint32_t mibitem;
	p80211msg_dot11req_mibset_t msg;
	int result;
	int err = 0;
	u16 shortretry, longretry, lifetime;

	msg.msgcode = DIDmsg_dot11req_mibget;
	mibitem.did = DIDmib_dot11mac_dot11OperationTable_dot11ShortRetryLimit;

	memcpy(&msg.mibattribute.data, &mibitem, sizeof(mibitem));
	result = p80211req_dorequest(wlandev, (u8 *) & msg);

	if (result) {
		err = -EFAULT;
		goto exit;
	}

	memcpy(&mibitem, &msg.mibattribute.data, sizeof(mibitem));

	shortretry = mibitem.data;

	mibitem.did = DIDmib_dot11mac_dot11OperationTable_dot11LongRetryLimit;

	memcpy(&msg.mibattribute.data, &mibitem, sizeof(mibitem));
	result = p80211req_dorequest(wlandev, (u8 *) & msg);

	if (result) {
		err = -EFAULT;
		goto exit;
	}

	memcpy(&mibitem, &msg.mibattribute.data, sizeof(mibitem));

	longretry = mibitem.data;

	mibitem.did =
	    DIDmib_dot11mac_dot11OperationTable_dot11MaxTransmitMSDULifetime;

	memcpy(&msg.mibattribute.data, &mibitem, sizeof(mibitem));
	result = p80211req_dorequest(wlandev, (u8 *) & msg);

	if (result) {
		err = -EFAULT;
		goto exit;
	}

	memcpy(&mibitem, &msg.mibattribute.data, sizeof(mibitem));

	lifetime = mibitem.data;

	rrq->disabled = 0;

	if ((rrq->flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) {
		rrq->flags = IW_RETRY_LIFETIME;
		rrq->value = lifetime * 1024;
	} else {
		if (rrq->flags & IW_RETRY_LONG) {
			rrq->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
			rrq->value = longretry;
		} else {
			rrq->flags = IW_RETRY_LIMIT;
			rrq->value = shortretry;
			if (shortretry != longretry)
				rrq->flags |= IW_RETRY_SHORT;
		}
	}

exit:
	return err;

}