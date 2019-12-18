#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_7__ {int txq_id; int state; } ;
struct il_tid_data {int seq_number; TYPE_3__ agg; } ;
struct il_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  sta_lock; TYPE_4__* stations; TYPE_2__* txq; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {struct il_tid_data* tid; } ;
struct TYPE_5__ {int write_ptr; int read_ptr; } ;
struct TYPE_6__ {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_HT (char*) ; 
 int ENXIO ; 
 int IEEE80211_SCTL_SEQ ; 
 int IL_AGG_OFF ; 
#define  IL_AGG_ON 129 
#define  IL_EMPTYING_HW_QUEUE_ADDBA 128 
 int IL_EMPTYING_HW_QUEUE_DELBA ; 
 int /*<<< orphan*/  IL_ERR (char*,size_t) ; 
 int IL_INVALID_STATION ; 
 int /*<<< orphan*/  IL_WARN (char*) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int il4965_get_fifo_from_tid (size_t) ; 
 int /*<<< orphan*/  il4965_txq_agg_disable (struct il_priv*,int,int,int) ; 
 int il_sta_id (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int
il4965_tx_agg_stop(struct il_priv *il, struct ieee80211_vif *vif,
		   struct ieee80211_sta *sta, u16 tid)
{
	int tx_fifo_id, txq_id, sta_id, ssn;
	struct il_tid_data *tid_data;
	int write_ptr, read_ptr;
	unsigned long flags;

	/* FIXME: warning if tx_fifo_id not found ? */
	tx_fifo_id = il4965_get_fifo_from_tid(tid);
	if (unlikely(tx_fifo_id < 0))
		return tx_fifo_id;

	sta_id = il_sta_id(sta);

	if (sta_id == IL_INVALID_STATION) {
		IL_ERR("Invalid station for AGG tid %d\n", tid);
		return -ENXIO;
	}

	spin_lock_irqsave(&il->sta_lock, flags);

	tid_data = &il->stations[sta_id].tid[tid];
	ssn = (tid_data->seq_number & IEEE80211_SCTL_SEQ) >> 4;
	txq_id = tid_data->agg.txq_id;

	switch (il->stations[sta_id].tid[tid].agg.state) {
	case IL_EMPTYING_HW_QUEUE_ADDBA:
		/*
		 * This can happen if the peer stops aggregation
		 * again before we've had a chance to drain the
		 * queue we selected previously, i.e. before the
		 * session was really started completely.
		 */
		D_HT("AGG stop before setup done\n");
		goto turn_off;
	case IL_AGG_ON:
		break;
	default:
		IL_WARN("Stopping AGG while state not ON or starting\n");
	}

	write_ptr = il->txq[txq_id].q.write_ptr;
	read_ptr = il->txq[txq_id].q.read_ptr;

	/* The queue is not empty */
	if (write_ptr != read_ptr) {
		D_HT("Stopping a non empty AGG HW QUEUE\n");
		il->stations[sta_id].tid[tid].agg.state =
		    IL_EMPTYING_HW_QUEUE_DELBA;
		spin_unlock_irqrestore(&il->sta_lock, flags);
		return 0;
	}

	D_HT("HW queue is empty\n");
turn_off:
	il->stations[sta_id].tid[tid].agg.state = IL_AGG_OFF;

	/* do not restore/save irqs */
	spin_unlock(&il->sta_lock);
	spin_lock(&il->lock);

	/*
	 * the only reason this call can fail is queue number out of range,
	 * which can happen if uCode is reloaded and all the station
	 * information are lost. if it is outside the range, there is no need
	 * to deactivate the uCode queue, just return "success" to allow
	 *  mac80211 to clean up it own data.
	 */
	il4965_txq_agg_disable(il, txq_id, ssn, tx_fifo_id);
	spin_unlock_irqrestore(&il->lock, flags);

	ieee80211_stop_tx_ba_cb_irqsafe(vif, sta->addr, tid);

	return 0;
}