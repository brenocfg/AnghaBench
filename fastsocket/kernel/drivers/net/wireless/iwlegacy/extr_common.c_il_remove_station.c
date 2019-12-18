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
typedef  size_t u8 ;
struct il_priv {scalar_t__ num_stations; int /*<<< orphan*/  sta_lock; TYPE_1__* stations; } ;
struct TYPE_2__ {int used; int /*<<< orphan*/ * lq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  D_ASSOC (char*,size_t const,size_t const*) ; 
 int /*<<< orphan*/  D_INFO (char*,size_t const*) ; 
 int EINVAL ; 
 size_t const IL_INVALID_STATION ; 
 int IL_STA_DRIVER_ACTIVE ; 
 int IL_STA_LOCAL ; 
 int IL_STA_UCODE_ACTIVE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  il_is_ready (struct il_priv*) ; 
 int il_send_remove_station (struct il_priv*,size_t const*,size_t const,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
il_remove_station(struct il_priv *il, const u8 sta_id, const u8 * addr)
{
	unsigned long flags;

	if (!il_is_ready(il)) {
		D_INFO("Unable to remove station %pM, device not ready.\n",
		       addr);
		/*
		 * It is typical for stations to be removed when we are
		 * going down. Return success since device will be down
		 * soon anyway
		 */
		return 0;
	}

	D_ASSOC("Removing STA from driver:%d  %pM\n", sta_id, addr);

	if (WARN_ON(sta_id == IL_INVALID_STATION))
		return -EINVAL;

	spin_lock_irqsave(&il->sta_lock, flags);

	if (!(il->stations[sta_id].used & IL_STA_DRIVER_ACTIVE)) {
		D_INFO("Removing %pM but non DRIVER active\n", addr);
		goto out_err;
	}

	if (!(il->stations[sta_id].used & IL_STA_UCODE_ACTIVE)) {
		D_INFO("Removing %pM but non UCODE active\n", addr);
		goto out_err;
	}

	if (il->stations[sta_id].used & IL_STA_LOCAL) {
		kfree(il->stations[sta_id].lq);
		il->stations[sta_id].lq = NULL;
	}

	il->stations[sta_id].used &= ~IL_STA_DRIVER_ACTIVE;

	il->num_stations--;

	BUG_ON(il->num_stations < 0);

	spin_unlock_irqrestore(&il->sta_lock, flags);

	return il_send_remove_station(il, addr, sta_id, false);
out_err:
	spin_unlock_irqrestore(&il->sta_lock, flags);
	return -EINVAL;
}