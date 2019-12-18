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
typedef  int /*<<< orphan*/  u8 ;
struct mac_configuration_cmd {TYPE_1__* config_table; } ;
struct bnx2x_raw_obj {int /*<<< orphan*/  rdata_mapping; int /*<<< orphan*/  cid; int /*<<< orphan*/  (* clear_pending ) (struct bnx2x_raw_obj*) ;scalar_t__ rdata; } ;
struct bnx2x_mcast_ramrod_params {int /*<<< orphan*/  ramrod_flags; struct bnx2x_mcast_obj* mcast_obj; } ;
struct bnx2x_mcast_obj {int max_cmd_len; int total_pending_num; int /*<<< orphan*/  (* clear_sched ) (struct bnx2x_mcast_obj*) ;int /*<<< orphan*/  pending_cmds_head; struct bnx2x_raw_obj raw; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  MAC_CONFIGURATION_ENTRY_ACTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_SET_MAC ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_ETH_MAC_COMMAND_INVALIDATE ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bnx2x_mcast_handle_current_cmd (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int,int /*<<< orphan*/ ) ; 
 int bnx2x_mcast_handle_pending_cmds_e1 (struct bnx2x*,struct bnx2x_mcast_ramrod_params*) ; 
 int bnx2x_mcast_refresh_registry_e1 (struct bnx2x*,struct bnx2x_mcast_obj*) ; 
 int /*<<< orphan*/  bnx2x_mcast_set_rdata_hdr_e1 (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mac_configuration_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_mcast_obj*) ; 
 int /*<<< orphan*/  stub2 (struct bnx2x_raw_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_mcast_setup_e1(struct bnx2x *bp,
				struct bnx2x_mcast_ramrod_params *p,
				enum bnx2x_mcast_cmd cmd)
{
	struct bnx2x_mcast_obj *o = p->mcast_obj;
	struct bnx2x_raw_obj *raw = &o->raw;
	struct mac_configuration_cmd *data =
		(struct mac_configuration_cmd *)(raw->rdata);
	int cnt = 0, i, rc;

	/* Reset the ramrod data buffer */
	memset(data, 0, sizeof(*data));

	/* First set all entries as invalid */
	for (i = 0; i < o->max_cmd_len ; i++)
		SET_FLAG(data->config_table[i].flags,
			 MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			 T_ETH_MAC_COMMAND_INVALIDATE);

	/* Handle pending commands first */
	cnt = bnx2x_mcast_handle_pending_cmds_e1(bp, p);

	/* If there are no more pending commands - clear SCHEDULED state */
	if (list_empty(&o->pending_cmds_head))
		o->clear_sched(o);

	/* The below may be true iff there were no pending commands */
	if (!cnt)
		cnt = bnx2x_mcast_handle_current_cmd(bp, p, cmd, 0);

	/* For 57710 every command has o->max_cmd_len length to ensure that
	 * commands are done one at a time.
	 */
	o->total_pending_num -= o->max_cmd_len;

	/* send a ramrod */

	WARN_ON(cnt > o->max_cmd_len);

	/* Set ramrod header (in particular, a number of entries to update) */
	bnx2x_mcast_set_rdata_hdr_e1(bp, p, (u8)cnt);

	/* update a registry: we need the registry contents to be always up
	 * to date in order to be able to execute a RESTORE opcode. Here
	 * we use the fact that for 57710 we sent one command at a time
	 * hence we may take the registry update out of the command handling
	 * and do it in a simpler way here.
	 */
	rc = bnx2x_mcast_refresh_registry_e1(bp, o);
	if (rc)
		return rc;

	/* If CLEAR_ONLY was requested - don't send a ramrod and clear
	 * RAMROD_PENDING status immediately.
	 */
	if (test_bit(RAMROD_DRV_CLR_ONLY, &p->ramrod_flags)) {
		raw->clear_pending(raw);
		return 0;
	} else {
		/* No need for an explicit memory barrier here as long we would
		 * need to ensure the ordering of writing to the SPQ element
		 * and updating of the SPQ producer which involves a memory
		 * read and we will have to put a full memory barrier there
		 * (inside bnx2x_sp_post()).
		 */

		/* Send a ramrod */
		rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_SET_MAC, raw->cid,
				   U64_HI(raw->rdata_mapping),
				   U64_LO(raw->rdata_mapping),
				   ETH_CONNECTION_TYPE);
		if (rc)
			return rc;

		/* Ramrod completion is pending */
		return 1;
	}
}