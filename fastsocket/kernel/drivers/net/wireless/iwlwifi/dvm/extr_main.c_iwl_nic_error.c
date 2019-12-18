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
struct iwl_priv {TYPE_1__* fw; } ;
struct iwl_op_mode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_priv* IWL_OP_MODE_GET_DVM (struct iwl_op_mode*) ; 
 int /*<<< orphan*/  iwl_dump_nic_error_log (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_dump_nic_event_log (struct iwl_priv*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwlagn_fw_error (struct iwl_priv*,int) ; 

__attribute__((used)) static void iwl_nic_error(struct iwl_op_mode *op_mode)
{
	struct iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	IWL_ERR(priv, "Loaded firmware version: %s\n",
		priv->fw->fw_version);

	iwl_dump_nic_error_log(priv);
	iwl_dump_nic_event_log(priv, false, NULL);

	iwlagn_fw_error(priv, false);
}