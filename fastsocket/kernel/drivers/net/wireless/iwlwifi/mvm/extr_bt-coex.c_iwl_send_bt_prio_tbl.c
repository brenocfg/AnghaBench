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
struct iwl_mvm {int dummy; } ;
struct iwl_bt_coex_prio_tbl_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_COEX_PRIO_TABLE ; 
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  iwl_bt_prio_tbl ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int iwl_send_bt_prio_tbl(struct iwl_mvm *mvm)
{
	return iwl_mvm_send_cmd_pdu(mvm, BT_COEX_PRIO_TABLE, CMD_SYNC,
				    sizeof(struct iwl_bt_coex_prio_tbl_cmd),
				    &iwl_bt_prio_tbl);
}