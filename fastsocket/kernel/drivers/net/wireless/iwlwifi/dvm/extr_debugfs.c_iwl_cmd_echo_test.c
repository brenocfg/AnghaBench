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
struct iwl_host_cmd {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,int) ; 
 int /*<<< orphan*/  REPLY_ECHO ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 

__attribute__((used)) static int iwl_cmd_echo_test(struct iwl_priv *priv)
{
	int ret;
	struct iwl_host_cmd cmd = {
		.id = REPLY_ECHO,
		.len = { 0 },
		.flags = CMD_SYNC,
	};

	ret = iwl_dvm_send_cmd(priv, &cmd);
	if (ret)
		IWL_ERR(priv, "echo testing fail: 0X%x\n", ret);
	else
		IWL_DEBUG_INFO(priv, "echo testing pass\n");
	return ret;
}