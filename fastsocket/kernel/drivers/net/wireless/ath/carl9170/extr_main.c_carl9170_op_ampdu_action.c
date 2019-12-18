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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ar9170* priv; } ;
struct carl9170_sta_tid {size_t hsn; size_t bsn; size_t snx; size_t tid; int /*<<< orphan*/  state; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  tmp_list; int /*<<< orphan*/  max; } ;
struct carl9170_sta_info {TYPE_1__* stats; int /*<<< orphan*/ * agg; int /*<<< orphan*/  ampdu_max_len; int /*<<< orphan*/  ht_sta; } ;
struct ar9170 {int /*<<< orphan*/  ampdu_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_ampdu_list_lock; int /*<<< orphan*/  tx_ampdu_list; int /*<<< orphan*/  tx_ampdu_list_len; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;
struct TYPE_2__ {int clear; int req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_BAW_SIZE ; 
 int /*<<< orphan*/  CARL9170_TID_STATE_IDLE ; 
 int /*<<< orphan*/  CARL9170_TID_STATE_PROGRESS ; 
 int /*<<< orphan*/  CARL9170_TID_STATE_SHUTDOWN ; 
 int EBUSY ; 
 int EFAULT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 struct carl9170_sta_tid* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ modparam_noht ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct carl9170_sta_tid*) ; 
 struct carl9170_sta_tid* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int carl9170_op_ampdu_action(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    enum ieee80211_ampdu_mlme_action action,
				    struct ieee80211_sta *sta,
				    u16 tid, u16 *ssn, u8 buf_size)
{
	struct ar9170 *ar = hw->priv;
	struct carl9170_sta_info *sta_info = (void *) sta->drv_priv;
	struct carl9170_sta_tid *tid_info;

	if (modparam_noht)
		return -EOPNOTSUPP;

	switch (action) {
	case IEEE80211_AMPDU_TX_START:
		if (!sta_info->ht_sta)
			return -EOPNOTSUPP;

		rcu_read_lock();
		if (rcu_dereference(sta_info->agg[tid])) {
			rcu_read_unlock();
			return -EBUSY;
		}

		tid_info = kzalloc(sizeof(struct carl9170_sta_tid),
				   GFP_ATOMIC);
		if (!tid_info) {
			rcu_read_unlock();
			return -ENOMEM;
		}

		tid_info->hsn = tid_info->bsn = tid_info->snx = (*ssn);
		tid_info->state = CARL9170_TID_STATE_PROGRESS;
		tid_info->tid = tid;
		tid_info->max = sta_info->ampdu_max_len;

		INIT_LIST_HEAD(&tid_info->list);
		INIT_LIST_HEAD(&tid_info->tmp_list);
		skb_queue_head_init(&tid_info->queue);
		spin_lock_init(&tid_info->lock);

		spin_lock_bh(&ar->tx_ampdu_list_lock);
		ar->tx_ampdu_list_len++;
		list_add_tail_rcu(&tid_info->list, &ar->tx_ampdu_list);
		rcu_assign_pointer(sta_info->agg[tid], tid_info);
		spin_unlock_bh(&ar->tx_ampdu_list_lock);
		rcu_read_unlock();

		ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;

	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		rcu_read_lock();
		tid_info = rcu_dereference(sta_info->agg[tid]);
		if (tid_info) {
			spin_lock_bh(&ar->tx_ampdu_list_lock);
			if (tid_info->state > CARL9170_TID_STATE_SHUTDOWN)
				tid_info->state = CARL9170_TID_STATE_SHUTDOWN;
			spin_unlock_bh(&ar->tx_ampdu_list_lock);
		}

		RCU_INIT_POINTER(sta_info->agg[tid], NULL);
		rcu_read_unlock();

		ieee80211_stop_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		ieee80211_queue_work(ar->hw, &ar->ampdu_work);
		break;

	case IEEE80211_AMPDU_TX_OPERATIONAL:
		rcu_read_lock();
		tid_info = rcu_dereference(sta_info->agg[tid]);

		sta_info->stats[tid].clear = true;
		sta_info->stats[tid].req = false;

		if (tid_info) {
			bitmap_zero(tid_info->bitmap, CARL9170_BAW_SIZE);
			tid_info->state = CARL9170_TID_STATE_IDLE;
		}
		rcu_read_unlock();

		if (WARN_ON_ONCE(!tid_info))
			return -EFAULT;

		break;

	case IEEE80211_AMPDU_RX_START:
	case IEEE80211_AMPDU_RX_STOP:
		/* Handled by hardware */
		break;

	default:
		return -EOPNOTSUPP;
	}

	return 0;
}