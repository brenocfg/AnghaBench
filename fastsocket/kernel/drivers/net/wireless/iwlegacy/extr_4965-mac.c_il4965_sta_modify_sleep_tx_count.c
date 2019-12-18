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
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_2__* stations; } ;
struct TYPE_4__ {int /*<<< orphan*/  modify_mask; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  sleep_tx_count; TYPE_1__ sta; int /*<<< orphan*/  station_flags_msk; int /*<<< orphan*/  station_flags; } ;
struct TYPE_5__ {TYPE_3__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  STA_CONTROL_MODIFY_MSK ; 
 int /*<<< orphan*/  STA_FLG_PWR_SAVE_MSK ; 
 int /*<<< orphan*/  STA_MODIFY_SLEEP_TX_COUNT_MSK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  il_send_add_sta (struct il_priv*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il4965_sta_modify_sleep_tx_count(struct il_priv *il, int sta_id, int cnt)
{
	unsigned long flags;

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].sta.station_flags |= STA_FLG_PWR_SAVE_MSK;
	il->stations[sta_id].sta.station_flags_msk = STA_FLG_PWR_SAVE_MSK;
	il->stations[sta_id].sta.sta.modify_mask =
	    STA_MODIFY_SLEEP_TX_COUNT_MSK;
	il->stations[sta_id].sta.sleep_tx_count = cpu_to_le16(cnt);
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	il_send_add_sta(il, &il->stations[sta_id].sta, CMD_ASYNC);
	spin_unlock_irqrestore(&il->sta_lock, flags);

}