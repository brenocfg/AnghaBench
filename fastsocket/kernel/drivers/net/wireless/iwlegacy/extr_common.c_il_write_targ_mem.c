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
typedef  int /*<<< orphan*/  u32 ;
struct il_priv {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBUS_TARG_MEM_WADDR ; 
 int /*<<< orphan*/  HBUS_TARG_MEM_WDAT ; 
 int /*<<< orphan*/  _il_grab_nic_access (struct il_priv*) ; 
 int /*<<< orphan*/  _il_release_nic_access (struct il_priv*) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il_write_targ_mem(struct il_priv *il, u32 addr, u32 val)
{
	unsigned long reg_flags;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	if (likely(_il_grab_nic_access(il))) {
		_il_wr(il, HBUS_TARG_MEM_WADDR, addr);
		_il_wr(il, HBUS_TARG_MEM_WDAT, val);
		_il_release_nic_access(il);
	}
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
}