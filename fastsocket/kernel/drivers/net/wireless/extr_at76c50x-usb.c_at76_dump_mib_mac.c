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
struct mib_mac {int /*<<< orphan*/  desired_bsstype; int /*<<< orphan*/  desired_bssid; int /*<<< orphan*/  desired_ssid; int /*<<< orphan*/  listen_interval; int /*<<< orphan*/  max_channel_time; int /*<<< orphan*/  min_channel_time; int /*<<< orphan*/  probe_delay; int /*<<< orphan*/  scan_channel; int /*<<< orphan*/  scan_type; int /*<<< orphan*/  long_retry_time; int /*<<< orphan*/  short_retry_time; int /*<<< orphan*/  cwmax; int /*<<< orphan*/  cwmin; int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; int /*<<< orphan*/  max_rx_lifetime; int /*<<< orphan*/  max_tx_msdu_lifetime; } ;
struct at76_priv {TYPE_1__* hw; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MIB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  MIB_MAC ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int at76_get_mib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mib_mac*,int) ; 
 int /*<<< orphan*/  hex2str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mib_mac*) ; 
 struct mib_mac* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at76_dump_mib_mac(struct at76_priv *priv)
{
	int ret;
	struct mib_mac *m = kmalloc(sizeof(struct mib_mac), GFP_KERNEL);

	if (!m)
		return;

	ret = at76_get_mib(priv->udev, MIB_MAC, m, sizeof(struct mib_mac));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MAC) failed: %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MAC: max_tx_msdu_lifetime %d "
		 "max_rx_lifetime %d frag_threshold %d rts_threshold %d "
		 "cwmin %d cwmax %d short_retry_time %d long_retry_time %d "
		 "scan_type %d scan_channel %d probe_delay %u "
		 "min_channel_time %d max_channel_time %d listen_int %d "
		 "desired_ssid %s desired_bssid %pM desired_bsstype %d",
		 wiphy_name(priv->hw->wiphy),
		 le32_to_cpu(m->max_tx_msdu_lifetime),
		 le32_to_cpu(m->max_rx_lifetime),
		 le16_to_cpu(m->frag_threshold), le16_to_cpu(m->rts_threshold),
		 le16_to_cpu(m->cwmin), le16_to_cpu(m->cwmax),
		 m->short_retry_time, m->long_retry_time, m->scan_type,
		 m->scan_channel, le16_to_cpu(m->probe_delay),
		 le16_to_cpu(m->min_channel_time),
		 le16_to_cpu(m->max_channel_time),
		 le16_to_cpu(m->listen_interval),
		 hex2str(m->desired_ssid, IW_ESSID_MAX_SIZE),
		 m->desired_bssid, m->desired_bsstype);
exit:
	kfree(m);
}