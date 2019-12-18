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
struct TYPE_4__ {int max_stations; } ;
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_1__* stations; TYPE_2__ hw_params; } ;
struct TYPE_3__ {int used; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int IL_STA_UCODE_ACTIVE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il_clear_ucode_stations(struct il_priv *il)
{
	int i;
	unsigned long flags_spin;
	bool cleared = false;

	D_INFO("Clearing ucode stations in driver\n");

	spin_lock_irqsave(&il->sta_lock, flags_spin);
	for (i = 0; i < il->hw_params.max_stations; i++) {
		if (il->stations[i].used & IL_STA_UCODE_ACTIVE) {
			D_INFO("Clearing ucode active for station %d\n", i);
			il->stations[i].used &= ~IL_STA_UCODE_ACTIVE;
			cleared = true;
		}
	}
	spin_unlock_irqrestore(&il->sta_lock, flags_spin);

	if (!cleared)
		D_INFO("No active stations found to be cleared\n");
}