#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct statistics_tx {scalar_t__ temperature; } ;
struct statistics_rx_phy {scalar_t__ temperature; } ;
struct statistics_rx_non_phy {scalar_t__ temperature; } ;
struct statistics_rx_ht_phy {scalar_t__ temperature; } ;
struct statistics_general_common {scalar_t__ temperature; } ;
struct statistics_bt_activity {scalar_t__ temperature; } ;
struct TYPE_15__ {scalar_t__ cmd; } ;
struct iwl_rx_packet {TYPE_6__ hdr; int /*<<< orphan*/  data; int /*<<< orphan*/  len_n_flags; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct TYPE_18__ {scalar_t__ temperature; } ;
struct TYPE_17__ {int flag; int /*<<< orphan*/  lock; TYPE_9__ bt_activity; TYPE_9__ tx; TYPE_9__ rx_cck; TYPE_9__ rx_ofdm_ht; TYPE_9__ rx_ofdm; TYPE_9__ rx_non_phy; TYPE_9__ common; int /*<<< orphan*/  accum_num_bt_kills; int /*<<< orphan*/  num_bt_kills; } ;
struct iwl_priv {unsigned long rx_statistics_jiffies; TYPE_8__ statistics; TYPE_7__* lib; int /*<<< orphan*/  run_time_calib_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  status; int /*<<< orphan*/  statistics_periodic; } ;
struct TYPE_14__ {struct statistics_tx cck; struct statistics_tx ofdm_ht; struct statistics_tx ofdm; struct statistics_tx general; } ;
struct TYPE_13__ {struct statistics_tx common; } ;
struct iwl_notif_statistics {int flag; struct statistics_tx tx; TYPE_5__ rx; TYPE_4__ general; } ;
struct iwl_device_cmd {int dummy; } ;
struct iwl_cmd_header {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  num_bt_kills; struct statistics_tx common; } ;
struct TYPE_12__ {TYPE_2__ general; struct statistics_tx cck; struct statistics_tx ofdm_ht; struct statistics_tx ofdm; } ;
struct TYPE_10__ {struct statistics_tx activity; struct statistics_tx common; } ;
struct iwl_bt_notif_statistics {int flag; TYPE_3__ rx; TYPE_1__ general; struct statistics_tx tx; } ;
typedef  int __le32 ;
struct TYPE_16__ {int /*<<< orphan*/  (* temperature ) (struct iwl_priv*) ;} ;

/* Variables and functions */
 int FH_RSCSR_FRAME_SIZE_MSK ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_priv*,char*,int) ; 
 scalar_t__ STATISTICS_NOTIFICATION ; 
 int STATISTICS_REPLY_FLG_HT40_MODE_MSK ; 
 int /*<<< orphan*/  STATUS_SCANNING ; 
 int /*<<< orphan*/  STATUS_STATISTICS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,int,int) ; 
 int /*<<< orphan*/  iwlagn_accumulative_statistics (struct iwl_priv*,struct statistics_tx*,struct statistics_tx*,struct statistics_tx*,struct statistics_tx*,struct statistics_tx*,struct statistics_tx*,struct statistics_tx*) ; 
 int /*<<< orphan*/  iwlagn_recover_from_statistics (struct iwl_priv*,struct statistics_tx*,struct statistics_tx*,struct statistics_tx*,unsigned long) ; 
 int /*<<< orphan*/  iwlagn_rx_calc_noise (struct iwl_priv*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_9__*,struct statistics_tx*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int const) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iwl_priv*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int iwlagn_rx_statistics(struct iwl_priv *priv,
			      struct iwl_rx_cmd_buffer *rxb,
			      struct iwl_device_cmd *cmd)
{
	unsigned long stamp = jiffies;
	const int reg_recalib_period = 60;
	int change;
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	u32 len = le32_to_cpu(pkt->len_n_flags) & FH_RSCSR_FRAME_SIZE_MSK;
	__le32 *flag;
	struct statistics_general_common *common;
	struct statistics_rx_non_phy *rx_non_phy;
	struct statistics_rx_phy *rx_ofdm;
	struct statistics_rx_ht_phy *rx_ofdm_ht;
	struct statistics_rx_phy *rx_cck;
	struct statistics_tx *tx;
	struct statistics_bt_activity *bt_activity;

	len -= sizeof(struct iwl_cmd_header); /* skip header */

	IWL_DEBUG_RX(priv, "Statistics notification received (%d bytes).\n",
		     len);

	spin_lock(&priv->statistics.lock);

	if (len == sizeof(struct iwl_bt_notif_statistics)) {
		struct iwl_bt_notif_statistics *stats;
		stats = (void *)&pkt->data;
		flag = &stats->flag;
		common = &stats->general.common;
		rx_non_phy = &stats->rx.general.common;
		rx_ofdm = &stats->rx.ofdm;
		rx_ofdm_ht = &stats->rx.ofdm_ht;
		rx_cck = &stats->rx.cck;
		tx = &stats->tx;
		bt_activity = &stats->general.activity;

#ifdef CONFIG_IWLWIFI_DEBUGFS
		/* handle this exception directly */
		priv->statistics.num_bt_kills = stats->rx.general.num_bt_kills;
		le32_add_cpu(&priv->statistics.accum_num_bt_kills,
			     le32_to_cpu(stats->rx.general.num_bt_kills));
#endif
	} else if (len == sizeof(struct iwl_notif_statistics)) {
		struct iwl_notif_statistics *stats;
		stats = (void *)&pkt->data;
		flag = &stats->flag;
		common = &stats->general.common;
		rx_non_phy = &stats->rx.general;
		rx_ofdm = &stats->rx.ofdm;
		rx_ofdm_ht = &stats->rx.ofdm_ht;
		rx_cck = &stats->rx.cck;
		tx = &stats->tx;
		bt_activity = NULL;
	} else {
		WARN_ONCE(1, "len %d doesn't match BT (%zu) or normal (%zu)\n",
			  len, sizeof(struct iwl_bt_notif_statistics),
			  sizeof(struct iwl_notif_statistics));
		spin_unlock(&priv->statistics.lock);
		return 0;
	}

	change = common->temperature != priv->statistics.common.temperature ||
		 (*flag & STATISTICS_REPLY_FLG_HT40_MODE_MSK) !=
		 (priv->statistics.flag & STATISTICS_REPLY_FLG_HT40_MODE_MSK);

	iwlagn_accumulative_statistics(priv, common, rx_non_phy, rx_ofdm,
				    rx_ofdm_ht, rx_cck, tx, bt_activity);

	iwlagn_recover_from_statistics(priv, rx_ofdm, rx_ofdm_ht, tx, stamp);

	priv->statistics.flag = *flag;
	memcpy(&priv->statistics.common, common, sizeof(*common));
	memcpy(&priv->statistics.rx_non_phy, rx_non_phy, sizeof(*rx_non_phy));
	memcpy(&priv->statistics.rx_ofdm, rx_ofdm, sizeof(*rx_ofdm));
	memcpy(&priv->statistics.rx_ofdm_ht, rx_ofdm_ht, sizeof(*rx_ofdm_ht));
	memcpy(&priv->statistics.rx_cck, rx_cck, sizeof(*rx_cck));
	memcpy(&priv->statistics.tx, tx, sizeof(*tx));
#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (bt_activity)
		memcpy(&priv->statistics.bt_activity, bt_activity,
			sizeof(*bt_activity));
#endif

	priv->rx_statistics_jiffies = stamp;

	set_bit(STATUS_STATISTICS, &priv->status);

	/* Reschedule the statistics timer to occur in
	 * reg_recalib_period seconds to ensure we get a
	 * thermal update even if the uCode doesn't give
	 * us one */
	mod_timer(&priv->statistics_periodic, jiffies +
		  msecs_to_jiffies(reg_recalib_period * 1000));

	if (unlikely(!test_bit(STATUS_SCANNING, &priv->status)) &&
	    (pkt->hdr.cmd == STATISTICS_NOTIFICATION)) {
		iwlagn_rx_calc_noise(priv);
		queue_work(priv->workqueue, &priv->run_time_calib_work);
	}
	if (priv->lib->temperature && change)
		priv->lib->temperature(priv);

	spin_unlock(&priv->statistics.lock);

	return 0;
}