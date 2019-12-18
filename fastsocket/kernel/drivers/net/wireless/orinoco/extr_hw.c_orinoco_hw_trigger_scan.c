#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hermes {TYPE_1__* ops; } ;
struct orinoco_private {scalar_t__ iw_mode; int firmware_type; int /*<<< orphan*/  has_ext_scan; scalar_t__ has_hostscan; struct hermes hw; struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct hermes_idstring {int /*<<< orphan*/  val; void* len; } ;
struct cfg80211_ssid {size_t ssid_len; int /*<<< orphan*/  ssid; } ;
typedef  void* __le16 ;
struct TYPE_2__ {int (* write_ltv ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hermes_idstring*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENETDOWN ; 
 int EOPNOTSUPP ; 
#define  FIRMWARE_TYPE_AGERE 130 
#define  FIRMWARE_TYPE_INTERSIL 129 
#define  FIRMWARE_TYPE_SYMBOL 128 
 int /*<<< orphan*/  HERMES_BYTES_TO_RECLEN (size_t) ; 
 int HERMES_HOSTSCAN_SYMBOL_BCAST ; 
 int HERMES_HOSTSCAN_SYMBOL_ONCE ; 
 int /*<<< orphan*/  HERMES_INQ_CHANNELINFO ; 
 int /*<<< orphan*/  HERMES_INQ_SCAN ; 
 int /*<<< orphan*/  HERMES_RID_CNFHOSTSCAN ; 
 int /*<<< orphan*/  HERMES_RID_CNFHOSTSCAN_SYMBOL ; 
 int /*<<< orphan*/  HERMES_RID_CNFSCANCHANNELS2GHZ ; 
 int /*<<< orphan*/  HERMES_RID_CNFSCANSSID_AGERE ; 
 int HERMES_WRITE_RECORD (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void***) ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  USER_BAP ; 
 void* cpu_to_le16 (size_t) ; 
 int hermes_inquire (struct hermes*,int /*<<< orphan*/ ) ; 
 int hermes_write_wordrec (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hermes_idstring*) ; 

int orinoco_hw_trigger_scan(struct orinoco_private *priv,
			    const struct cfg80211_ssid *ssid)
{
	struct net_device *dev = priv->ndev;
	struct hermes *hw = &priv->hw;
	unsigned long flags;
	int err = 0;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	/* Scanning with port 0 disabled would fail */
	if (!netif_running(dev)) {
		err = -ENETDOWN;
		goto out;
	}

	/* In monitor mode, the scan results are always empty.
	 * Probe responses are passed to the driver as received
	 * frames and could be processed in software. */
	if (priv->iw_mode == NL80211_IFTYPE_MONITOR) {
		err = -EOPNOTSUPP;
		goto out;
	}

	if (priv->has_hostscan) {
		switch (priv->firmware_type) {
		case FIRMWARE_TYPE_SYMBOL:
			err = hermes_write_wordrec(hw, USER_BAP,
						HERMES_RID_CNFHOSTSCAN_SYMBOL,
						HERMES_HOSTSCAN_SYMBOL_ONCE |
						HERMES_HOSTSCAN_SYMBOL_BCAST);
			break;
		case FIRMWARE_TYPE_INTERSIL: {
			__le16 req[3];

			req[0] = cpu_to_le16(0x3fff);	/* All channels */
			req[1] = cpu_to_le16(0x0001);	/* rate 1 Mbps */
			req[2] = 0;			/* Any ESSID */
			err = HERMES_WRITE_RECORD(hw, USER_BAP,
						  HERMES_RID_CNFHOSTSCAN, &req);
			break;
		}
		case FIRMWARE_TYPE_AGERE:
			if (ssid->ssid_len > 0) {
				struct hermes_idstring idbuf;
				size_t len = ssid->ssid_len;

				idbuf.len = cpu_to_le16(len);
				memcpy(idbuf.val, ssid->ssid, len);

				err = hw->ops->write_ltv(hw, USER_BAP,
					       HERMES_RID_CNFSCANSSID_AGERE,
					       HERMES_BYTES_TO_RECLEN(len + 2),
					       &idbuf);
			} else
				err = hermes_write_wordrec(hw, USER_BAP,
						   HERMES_RID_CNFSCANSSID_AGERE,
						   0);	/* Any ESSID */
			if (err)
				break;

			if (priv->has_ext_scan) {
				err = hermes_write_wordrec(hw, USER_BAP,
						HERMES_RID_CNFSCANCHANNELS2GHZ,
						0x7FFF);
				if (err)
					goto out;

				err = hermes_inquire(hw,
						     HERMES_INQ_CHANNELINFO);
			} else
				err = hermes_inquire(hw, HERMES_INQ_SCAN);

			break;
		}
	} else
		err = hermes_inquire(hw, HERMES_INQ_SCAN);

 out:
	orinoco_unlock(priv, &flags);

	return err;
}