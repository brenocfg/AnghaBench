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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_priv {TYPE_1__* fw; } ;
struct iwl_op_mode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_ver; } ;

/* Variables and functions */
 struct iwl_priv* IWL_OP_MODE_GET_DVM (struct iwl_op_mode*) ; 

__attribute__((used)) static u32 iwl_testmode_get_fw_ver(struct iwl_op_mode *op_mode)
{
	struct iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);
	return priv->fw->ucode_ver;
}