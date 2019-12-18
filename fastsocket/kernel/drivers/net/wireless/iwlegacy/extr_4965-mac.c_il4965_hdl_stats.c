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
struct TYPE_16__ {scalar_t__ cmd; } ;
struct TYPE_12__ {scalar_t__ temperature; } ;
struct TYPE_13__ {TYPE_3__ common; } ;
struct TYPE_18__ {int flag; TYPE_4__ general; } ;
struct TYPE_15__ {TYPE_9__ stats; } ;
struct il_rx_pkt {TYPE_7__ hdr; TYPE_6__ u; int /*<<< orphan*/  len_n_flags; } ;
struct il_rx_buf {int dummy; } ;
struct TYPE_10__ {scalar_t__ temperature; } ;
struct TYPE_11__ {TYPE_1__ common; } ;
struct TYPE_17__ {int flag; TYPE_2__ general; } ;
struct TYPE_14__ {TYPE_8__ stats; } ;
struct il_priv {int /*<<< orphan*/  run_time_calib_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  status; int /*<<< orphan*/  stats_periodic; TYPE_5__ _4965; } ;
struct il_notif_stats {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_RX (char*,int,int) ; 
 int IL_RX_FRAME_SIZE_MSK ; 
 scalar_t__ N_STATS ; 
 int STATS_REPLY_FLG_HT40_MODE_MSK ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int /*<<< orphan*/  S_STATS ; 
 int /*<<< orphan*/  il4965_accumulative_stats (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il4965_rx_calc_noise (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_temperature_calib (struct il_priv*) ; 
 scalar_t__ jiffies ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int const) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
il4965_hdl_stats(struct il_priv *il, struct il_rx_buf *rxb)
{
	const int recalib_seconds = 60;
	bool change;
	struct il_rx_pkt *pkt = rxb_addr(rxb);

	D_RX("Statistics notification received (%d vs %d).\n",
	     (int)sizeof(struct il_notif_stats),
	     le32_to_cpu(pkt->len_n_flags) & IL_RX_FRAME_SIZE_MSK);

	change =
	    ((il->_4965.stats.general.common.temperature !=
	      pkt->u.stats.general.common.temperature) ||
	     ((il->_4965.stats.flag & STATS_REPLY_FLG_HT40_MODE_MSK) !=
	      (pkt->u.stats.flag & STATS_REPLY_FLG_HT40_MODE_MSK)));
#ifdef CONFIG_IWLEGACY_DEBUGFS
	il4965_accumulative_stats(il, (__le32 *) &pkt->u.stats);
#endif

	/* TODO: reading some of stats is unneeded */
	memcpy(&il->_4965.stats, &pkt->u.stats, sizeof(il->_4965.stats));

	set_bit(S_STATS, &il->status);

	/*
	 * Reschedule the stats timer to occur in recalib_seconds to ensure
	 * we get a thermal update even if the uCode doesn't give us one
	 */
	mod_timer(&il->stats_periodic,
		  jiffies + msecs_to_jiffies(recalib_seconds * 1000));

	if (unlikely(!test_bit(S_SCANNING, &il->status)) &&
	    (pkt->hdr.cmd == N_STATS)) {
		il4965_rx_calc_noise(il);
		queue_work(il->workqueue, &il->run_time_calib_work);
	}

	if (change)
		il4965_temperature_calib(il);
}