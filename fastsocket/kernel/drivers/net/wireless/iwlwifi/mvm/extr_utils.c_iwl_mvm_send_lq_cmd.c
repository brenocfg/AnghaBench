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
typedef  int u8 ;
struct iwl_mvm {int dummy; } ;
struct iwl_lq_cmd {scalar_t__ sta_id; } ;
struct iwl_host_cmd {int flags; int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int EINVAL ; 
 scalar_t__ IWL_MVM_STATION_COUNT ; 
 int /*<<< orphan*/  LQ_CMD ; 
 scalar_t__ WARN_ON (int) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 

int iwl_mvm_send_lq_cmd(struct iwl_mvm *mvm, struct iwl_lq_cmd *lq,
			u8 flags, bool init)
{
	struct iwl_host_cmd cmd = {
		.id = LQ_CMD,
		.len = { sizeof(struct iwl_lq_cmd), },
		.flags = flags,
		.data = { lq, },
	};

	if (WARN_ON(lq->sta_id == IWL_MVM_STATION_COUNT))
		return -EINVAL;

	if (WARN_ON(init && (cmd.flags & CMD_ASYNC)))
		return -EINVAL;

	return iwl_mvm_send_cmd(mvm, &cmd);
}