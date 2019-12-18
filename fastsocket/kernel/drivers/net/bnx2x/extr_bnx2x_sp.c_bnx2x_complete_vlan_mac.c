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
struct TYPE_2__ {scalar_t__ error; } ;
union event_ring_elem {TYPE_1__ message; } ;
struct bnx2x_raw_obj {int /*<<< orphan*/  (* clear_pending ) (struct bnx2x_raw_obj*) ;} ;
struct bnx2x_vlan_mac_obj {int /*<<< orphan*/  exe_queue; struct bnx2x_raw_obj raw; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RAMROD_CONT ; 
 int /*<<< orphan*/  bnx2x_exe_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_exe_queue_reset_pending (struct bnx2x*,int /*<<< orphan*/ *) ; 
 int bnx2x_exe_queue_step (struct bnx2x*,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_raw_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int bnx2x_complete_vlan_mac(struct bnx2x *bp,
				   struct bnx2x_vlan_mac_obj *o,
				   union event_ring_elem *cqe,
				   unsigned long *ramrod_flags)
{
	struct bnx2x_raw_obj *r = &o->raw;
	int rc;

	/* Reset pending list */
	bnx2x_exe_queue_reset_pending(bp, &o->exe_queue);

	/* Clear pending */
	r->clear_pending(r);

	/* If ramrod failed this is most likely a SW bug */
	if (cqe->message.error)
		return -EINVAL;

	/* Run the next bulk of pending commands if requested */
	if (test_bit(RAMROD_CONT, ramrod_flags)) {
		rc = bnx2x_exe_queue_step(bp, &o->exe_queue, ramrod_flags);
		if (rc < 0)
			return rc;
	}

	/* If there is more work to do return PENDING */
	if (!bnx2x_exe_queue_empty(&o->exe_queue))
		return 1;

	return 0;
}