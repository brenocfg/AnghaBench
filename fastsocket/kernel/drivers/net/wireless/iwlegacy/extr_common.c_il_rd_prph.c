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
 int /*<<< orphan*/  _il_grab_nic_access (struct il_priv*) ; 
 int /*<<< orphan*/  _il_rd_prph (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_release_nic_access (struct il_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32
il_rd_prph(struct il_priv *il, u32 reg)
{
	unsigned long reg_flags;
	u32 val;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	_il_grab_nic_access(il);
	val = _il_rd_prph(il, reg);
	_il_release_nic_access(il);
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
	return val;
}