#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct il_priv {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  hw; scalar_t__ mac80211_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1 ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_SET ; 
 int /*<<< orphan*/  D_POWER (char*) ; 
 int /*<<< orphan*/  _il_grab_nic_access (struct il_priv*) ; 
 int /*<<< orphan*/  _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_release_nic_access (struct il_priv*) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
il4965_perform_ct_kill_task(struct il_priv *il)
{
	unsigned long flags;

	D_POWER("Stop all queues\n");

	if (il->mac80211_registered)
		ieee80211_stop_queues(il->hw);

	_il_wr(il, CSR_UCODE_DRV_GP1_SET,
	       CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);
	_il_rd(il, CSR_UCODE_DRV_GP1);

	spin_lock_irqsave(&il->reg_lock, flags);
	if (likely(_il_grab_nic_access(il)))
		_il_release_nic_access(il);
	spin_unlock_irqrestore(&il->reg_lock, flags);
}