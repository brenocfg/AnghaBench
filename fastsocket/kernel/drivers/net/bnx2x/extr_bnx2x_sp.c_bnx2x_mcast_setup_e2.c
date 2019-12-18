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
typedef  int /*<<< orphan*/  u8 ;
struct eth_multicast_rules_ramrod_data {int dummy; } ;
struct bnx2x_raw_obj {int /*<<< orphan*/  rdata_mapping; int /*<<< orphan*/  cid; int /*<<< orphan*/  (* clear_pending ) (struct bnx2x_raw_obj*) ;scalar_t__ rdata; } ;
struct bnx2x_mcast_ramrod_params {scalar_t__ mcast_list_len; int /*<<< orphan*/  ramrod_flags; struct bnx2x_mcast_obj* mcast_obj; } ;
struct bnx2x_mcast_obj {scalar_t__ total_pending_num; int max_cmd_len; int /*<<< orphan*/  (* clear_sched ) (struct bnx2x_mcast_obj*) ;int /*<<< orphan*/  pending_cmds_head; struct bnx2x_raw_obj raw; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_MULTICAST_RULES ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bnx2x_mcast_handle_current_cmd (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int,int) ; 
 int bnx2x_mcast_handle_pending_cmds_e2 (struct bnx2x*,struct bnx2x_mcast_ramrod_params*) ; 
 int /*<<< orphan*/  bnx2x_mcast_refresh_registry_e2 (struct bnx2x*,struct bnx2x_mcast_obj*) ; 
 int /*<<< orphan*/  bnx2x_mcast_set_rdata_hdr_e2 (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct eth_multicast_rules_ramrod_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_mcast_obj*) ; 
 int /*<<< orphan*/  stub2 (struct bnx2x_raw_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_mcast_setup_e2(struct bnx2x *bp,
				struct bnx2x_mcast_ramrod_params *p,
				enum bnx2x_mcast_cmd cmd)
{
	struct bnx2x_raw_obj *raw = &p->mcast_obj->raw;
	struct bnx2x_mcast_obj *o = p->mcast_obj;
	struct eth_multicast_rules_ramrod_data *data =
		(struct eth_multicast_rules_ramrod_data *)(raw->rdata);
	int cnt = 0, rc;

	/* Reset the ramrod data buffer */
	memset(data, 0, sizeof(*data));

	cnt = bnx2x_mcast_handle_pending_cmds_e2(bp, p);

	/* If there are no more pending commands - clear SCHEDULED state */
	if (list_empty(&o->pending_cmds_head))
		o->clear_sched(o);

	/* The below may be true iff there was enough room in ramrod
	 * data for all pending commands and for the current
	 * command. Otherwise the current command would have been added
	 * to the pending commands and p->mcast_list_len would have been
	 * zeroed.
	 */
	if (p->mcast_list_len > 0)
		cnt = bnx2x_mcast_handle_current_cmd(bp, p, cmd, cnt);

	/* We've pulled out some MACs - update the total number of
	 * outstanding.
	 */
	o->total_pending_num -= cnt;

	/* send a ramrod */
	WARN_ON(o->total_pending_num < 0);
	WARN_ON(cnt > o->max_cmd_len);

	bnx2x_mcast_set_rdata_hdr_e2(bp, p, (u8)cnt);

	/* Update a registry size if there are no more pending operations.
	 *
	 * We don't want to change the value of the registry size if there are
	 * pending operations because we want it to always be equal to the
	 * exact or the approximate number (see bnx2x_mcast_validate_e2()) of
	 * set bins after the last requested operation in order to properly
	 * evaluate the size of the next DEL/RESTORE operation.
	 *
	 * Note that we update the registry itself during command(s) handling
	 * - see bnx2x_mcast_set_one_rule_e2(). That's because for 57712 we
	 * aggregate multiple commands (ADD/DEL/RESTORE) into one ramrod but
	 * with a limited amount of update commands (per MAC/bin) and we don't
	 * know in this scope what the actual state of bins configuration is
	 * going to be after this ramrod.
	 */
	if (!o->total_pending_num)
		bnx2x_mcast_refresh_registry_e2(bp, o);

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
		rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_MULTICAST_RULES,
				   raw->cid, U64_HI(raw->rdata_mapping),
				   U64_LO(raw->rdata_mapping),
				   ETH_CONNECTION_TYPE);
		if (rc)
			return rc;

		/* Ramrod completion is pending */
		return 1;
	}
}