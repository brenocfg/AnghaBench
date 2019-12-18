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
struct bnx2x_mcast_ramrod_params {int mcast_list_len; struct bnx2x_mcast_obj* mcast_obj; } ;
struct bnx2x_mcast_obj {int (* get_registry_size ) (struct bnx2x_mcast_obj*) ;int /*<<< orphan*/  total_pending_num; int /*<<< orphan*/  (* set_registry_size ) (struct bnx2x_mcast_obj*,int) ;} ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_MCAST_CMD_ADD 131 
#define  BNX2X_MCAST_CMD_CONT 130 
#define  BNX2X_MCAST_CMD_DEL 129 
#define  BNX2X_MCAST_CMD_RESTORE 128 
 int EINVAL ; 
 int stub1 (struct bnx2x_mcast_obj*) ; 
 int /*<<< orphan*/  stub2 (struct bnx2x_mcast_obj*,int) ; 
 int /*<<< orphan*/  stub3 (struct bnx2x_mcast_obj*,int) ; 

__attribute__((used)) static int bnx2x_mcast_validate_e2(struct bnx2x *bp,
				   struct bnx2x_mcast_ramrod_params *p,
				   enum bnx2x_mcast_cmd cmd)
{
	struct bnx2x_mcast_obj *o = p->mcast_obj;
	int reg_sz = o->get_registry_size(o);

	switch (cmd) {
	/* DEL command deletes all currently configured MACs */
	case BNX2X_MCAST_CMD_DEL:
		o->set_registry_size(o, 0);
		/* Don't break */

	/* RESTORE command will restore the entire multicast configuration */
	case BNX2X_MCAST_CMD_RESTORE:
		/* Here we set the approximate amount of work to do, which in
		 * fact may be only less as some MACs in postponed ADD
		 * command(s) scheduled before this command may fall into
		 * the same bin and the actual number of bins set in the
		 * registry would be less than we estimated here. See
		 * bnx2x_mcast_set_one_rule_e2() for further details.
		 */
		p->mcast_list_len = reg_sz;
		break;

	case BNX2X_MCAST_CMD_ADD:
	case BNX2X_MCAST_CMD_CONT:
		/* Here we assume that all new MACs will fall into new bins.
		 * However we will correct the real registry size after we
		 * handle all pending commands.
		 */
		o->set_registry_size(o, reg_sz + p->mcast_list_len);
		break;

	default:
		BNX2X_ERR("Unknown command: %d\n", cmd);
		return -EINVAL;
	}

	/* Increase the total number of MACs pending to be configured */
	o->total_pending_num += p->mcast_list_len;

	return 0;
}