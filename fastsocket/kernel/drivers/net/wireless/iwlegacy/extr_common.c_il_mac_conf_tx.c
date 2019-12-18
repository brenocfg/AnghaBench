#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {TYPE_1__* ac; } ;
struct TYPE_6__ {TYPE_2__ def_qos_parm; } ;
struct il_priv {int /*<<< orphan*/  lock; TYPE_3__ qos_data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int cw_min; int cw_max; int txop; int /*<<< orphan*/  aifs; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
struct TYPE_4__ {scalar_t__ reserved1; void* edca_txop; int /*<<< orphan*/  aifsn; void* cw_max; void* cw_min; } ;

/* Variables and functions */
 int AC_NUM ; 
 int /*<<< orphan*/  D_MAC80211 (char*,...) ; 
 int EIO ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  il_is_ready_rf (struct il_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
il_mac_conf_tx(struct ieee80211_hw *hw, struct ieee80211_vif *vif, u16 queue,
	       const struct ieee80211_tx_queue_params *params)
{
	struct il_priv *il = hw->priv;
	unsigned long flags;
	int q;

	D_MAC80211("enter\n");

	if (!il_is_ready_rf(il)) {
		D_MAC80211("leave - RF not ready\n");
		return -EIO;
	}

	if (queue >= AC_NUM) {
		D_MAC80211("leave - queue >= AC_NUM %d\n", queue);
		return 0;
	}

	q = AC_NUM - 1 - queue;

	spin_lock_irqsave(&il->lock, flags);

	il->qos_data.def_qos_parm.ac[q].cw_min =
	    cpu_to_le16(params->cw_min);
	il->qos_data.def_qos_parm.ac[q].cw_max =
	    cpu_to_le16(params->cw_max);
	il->qos_data.def_qos_parm.ac[q].aifsn = params->aifs;
	il->qos_data.def_qos_parm.ac[q].edca_txop =
	    cpu_to_le16((params->txop * 32));

	il->qos_data.def_qos_parm.ac[q].reserved1 = 0;

	spin_unlock_irqrestore(&il->lock, flags);

	D_MAC80211("leave\n");
	return 0;
}