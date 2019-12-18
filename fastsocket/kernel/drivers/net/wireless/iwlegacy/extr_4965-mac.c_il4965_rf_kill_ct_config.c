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
struct TYPE_2__ {int /*<<< orphan*/  ct_kill_threshold; } ;
struct il_priv {TYPE_1__ hw_params; int /*<<< orphan*/  lock; } ;
struct il_ct_kill_config {int /*<<< orphan*/  critical_temperature_R; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_CLR ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT ; 
 int /*<<< orphan*/  C_CT_KILL_CONFIG ; 
 int /*<<< orphan*/  D_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int il_send_cmd_pdu (struct il_priv*,int /*<<< orphan*/ ,int,struct il_ct_kill_config*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
il4965_rf_kill_ct_config(struct il_priv *il)
{
	struct il_ct_kill_config cmd;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&il->lock, flags);
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR,
	       CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);
	spin_unlock_irqrestore(&il->lock, flags);

	cmd.critical_temperature_R =
	    cpu_to_le32(il->hw_params.ct_kill_threshold);

	ret = il_send_cmd_pdu(il, C_CT_KILL_CONFIG, sizeof(cmd), &cmd);
	if (ret)
		IL_ERR("C_CT_KILL_CONFIG failed\n");
	else
		D_INFO("C_CT_KILL_CONFIG " "succeeded, "
		       "critical temperature is %d\n",
		       il->hw_params.ct_kill_threshold);
}