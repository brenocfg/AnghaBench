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
struct bnx2x_queue_sp_obj {unsigned long pending; scalar_t__ next_tx_only; scalar_t__ max_cos; scalar_t__ num_tx_only; int /*<<< orphan*/  next_state; int /*<<< orphan*/  state; int /*<<< orphan*/ * cids; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_queue_cmd { ____Placeholder_bnx2x_queue_cmd } bnx2x_queue_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 size_t BNX2X_PRIMARY_CID_INDEX ; 
 int /*<<< orphan*/  BNX2X_Q_STATE_MAX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,scalar_t__,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  test_and_clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int bnx2x_queue_comp_cmd(struct bnx2x *bp,
				struct bnx2x_queue_sp_obj *o,
				enum bnx2x_queue_cmd cmd)
{
	unsigned long cur_pending = o->pending;

	if (!test_and_clear_bit(cmd, &cur_pending)) {
		BNX2X_ERR("Bad MC reply %d for queue %d in state %d pending 0x%lx, next_state %d\n",
			  cmd, o->cids[BNX2X_PRIMARY_CID_INDEX],
			  o->state, cur_pending, o->next_state);
		return -EINVAL;
	}

	if (o->next_tx_only >= o->max_cos)
		/* >= because tx only must always be smaller than cos since the
		 * primary connection supports COS 0
		 */
		BNX2X_ERR("illegal value for next tx_only: %d. max cos was %d",
			   o->next_tx_only, o->max_cos);

	DP(BNX2X_MSG_SP,
	   "Completing command %d for queue %d, setting state to %d\n",
	   cmd, o->cids[BNX2X_PRIMARY_CID_INDEX], o->next_state);

	if (o->next_tx_only)  /* print num tx-only if any exist */
		DP(BNX2X_MSG_SP, "primary cid %d: num tx-only cons %d\n",
		   o->cids[BNX2X_PRIMARY_CID_INDEX], o->next_tx_only);

	o->state = o->next_state;
	o->num_tx_only = o->next_tx_only;
	o->next_state = BNX2X_Q_STATE_MAX;

	/* It's important that o->state and o->next_state are
	 * updated before o->pending.
	 */
	wmb();

	clear_bit(cmd, &o->pending);
	smp_mb__after_clear_bit();

	return 0;
}