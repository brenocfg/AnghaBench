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
struct iwl_priv {int dummy; } ;
struct iwl_op_mode {int dummy; } ;
struct iwl_host_cmd {int dummy; } ;

/* Variables and functions */
 struct iwl_priv* IWL_OP_MODE_GET_DVM (struct iwl_op_mode*) ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 

__attribute__((used)) static int iwl_testmode_send_cmd(struct iwl_op_mode *op_mode,
				 struct iwl_host_cmd *cmd)
{
	struct iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);
	return iwl_dvm_send_cmd(priv, cmd);
}