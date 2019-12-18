#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_stations; } ;
struct il_priv {scalar_t__ num_stations; int /*<<< orphan*/  sta_lock; TYPE_2__* stations; TYPE_1__ hw_params; } ;
struct TYPE_4__ {int used; int /*<<< orphan*/ * lq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IL_STA_BCAST ; 
 int IL_STA_UCODE_ACTIVE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il_dealloc_bcast_stations(struct il_priv *il)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&il->sta_lock, flags);
	for (i = 0; i < il->hw_params.max_stations; i++) {
		if (!(il->stations[i].used & IL_STA_BCAST))
			continue;

		il->stations[i].used &= ~IL_STA_UCODE_ACTIVE;
		il->num_stations--;
		BUG_ON(il->num_stations < 0);
		kfree(il->stations[i].lq);
		il->stations[i].lq = NULL;
	}
	spin_unlock_irqrestore(&il->sta_lock, flags);
}