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
struct iwl_priv {int /*<<< orphan*/  sta_lock; TYPE_2__* stations; int /*<<< orphan*/  mutex; } ;
struct iwl_addsta_cmd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  modify_mask; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  tid_disable_tx; TYPE_1__ sta; } ;
struct TYPE_5__ {TYPE_3__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  STA_CONTROL_MODIFY_MSK ; 
 int /*<<< orphan*/  STA_MODIFY_TID_DISABLE_TX ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int iwl_send_add_sta (struct iwl_priv*,struct iwl_addsta_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct iwl_addsta_cmd*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iwl_sta_tx_modify_enable_tid(struct iwl_priv *priv, int sta_id, int tid)
{
	struct iwl_addsta_cmd sta_cmd;

	lockdep_assert_held(&priv->mutex);

	/* Remove "disable" flag, to enable Tx for this TID */
	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].sta.sta.modify_mask = STA_MODIFY_TID_DISABLE_TX;
	priv->stations[sta_id].sta.tid_disable_tx &= cpu_to_le16(~(1 << tid));
	priv->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	memcpy(&sta_cmd, &priv->stations[sta_id].sta, sizeof(struct iwl_addsta_cmd));
	spin_unlock_bh(&priv->sta_lock);

	return iwl_send_add_sta(priv, &sta_cmd, CMD_SYNC);
}