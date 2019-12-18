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
typedef  int /*<<< orphan*/  wlandevice_t ;
typedef  int /*<<< orphan*/  u8 ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; scalar_t__ disabled; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ mibattribute; int /*<<< orphan*/  msgcode; } ;
typedef  TYPE_2__ p80211msg_dot11req_mibset_t ;
struct TYPE_9__ {int data; int /*<<< orphan*/  did; } ;
typedef  TYPE_3__ p80211item_uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/ * ml_priv; } ;
typedef  TYPE_4__ netdevice_t ;
typedef  int /*<<< orphan*/  mibitem ;

/* Variables and functions */
 int /*<<< orphan*/  DIDmib_dot11mac_dot11OperationTable_dot11LongRetryLimit ; 
 int /*<<< orphan*/  DIDmib_dot11mac_dot11OperationTable_dot11MaxTransmitMSDULifetime ; 
 int /*<<< orphan*/  DIDmib_dot11mac_dot11OperationTable_dot11ShortRetryLimit ; 
 int /*<<< orphan*/  DIDmsg_dot11req_mibset ; 
 int EFAULT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IW_RETRY_LIFETIME ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int IW_RETRY_TYPE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int p80211req_dorequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlan_wext_write ; 

__attribute__((used)) static int p80211wext_siwretry(netdevice_t *dev,
			       struct iw_request_info *info,
			       struct iw_param *rrq, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;
	p80211item_uint32_t mibitem;
	p80211msg_dot11req_mibset_t msg;
	int result;
	int err = 0;

	if (!wlan_wext_write) {
		err = (-EOPNOTSUPP);
		goto exit;
	}

	if (rrq->disabled) {
		err = -EINVAL;
		goto exit;
	}

	msg.msgcode = DIDmsg_dot11req_mibset;

	if ((rrq->flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) {
		mibitem.did =
		    DIDmib_dot11mac_dot11OperationTable_dot11MaxTransmitMSDULifetime;
		mibitem.data = rrq->value /= 1024;

		memcpy(&msg.mibattribute.data, &mibitem, sizeof(mibitem));
		result = p80211req_dorequest(wlandev, (u8 *) & msg);

		if (result) {
			err = -EFAULT;
			goto exit;
		}
	} else {
		if (rrq->flags & IW_RETRY_LONG) {
			mibitem.did =
			    DIDmib_dot11mac_dot11OperationTable_dot11LongRetryLimit;
			mibitem.data = rrq->value;

			memcpy(&msg.mibattribute.data, &mibitem,
			       sizeof(mibitem));
			result = p80211req_dorequest(wlandev, (u8 *) & msg);

			if (result) {
				err = -EFAULT;
				goto exit;
			}
		}

		if (rrq->flags & IW_RETRY_SHORT) {
			mibitem.did =
			    DIDmib_dot11mac_dot11OperationTable_dot11ShortRetryLimit;
			mibitem.data = rrq->value;

			memcpy(&msg.mibattribute.data, &mibitem,
			       sizeof(mibitem));
			result = p80211req_dorequest(wlandev, (u8 *) & msg);

			if (result) {
				err = -EFAULT;
				goto exit;
			}
		}
	}

exit:
	return err;

}