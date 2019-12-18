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
typedef  int u64 ;
struct amo {int dummy; } ;
struct TYPE_2__ {struct amo* amos_page; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int XPC_ACTIVATE_IRQ_AMOS_SN2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int find_first_bit (unsigned long*,int) ; 
 int find_next_bit (unsigned long*,int,int) ; 
 scalar_t__ xpc_exiting ; 
 int /*<<< orphan*/  xpc_identify_activate_IRQ_req_sn2 (int) ; 
 unsigned long* xpc_mach_nasids ; 
 int xpc_nasid_mask_nlongs ; 
 int /*<<< orphan*/  xpc_part ; 
 unsigned long xpc_receive_IRQ_amo_sn2 (struct amo*) ; 
 TYPE_1__* xpc_vars_sn2 ; 

int
xpc_identify_activate_IRQ_sender_sn2(void)
{
	int l;
	int b;
	unsigned long nasid_mask_long;
	u64 nasid;		/* remote nasid */
	int n_IRQs_detected = 0;
	struct amo *act_amos;

	act_amos = xpc_vars_sn2->amos_page + XPC_ACTIVATE_IRQ_AMOS_SN2;

	/* scan through activate amo variables looking for non-zero entries */
	for (l = 0; l < xpc_nasid_mask_nlongs; l++) {

		if (xpc_exiting)
			break;

		nasid_mask_long = xpc_receive_IRQ_amo_sn2(&act_amos[l]);

		b = find_first_bit(&nasid_mask_long, BITS_PER_LONG);
		if (b >= BITS_PER_LONG) {
			/* no IRQs from nasids in this amo variable */
			continue;
		}

		dev_dbg(xpc_part, "amo[%d] gave back 0x%lx\n", l,
			nasid_mask_long);

		/*
		 * If this nasid has been added to the machine since
		 * our partition was reset, this will retain the
		 * remote nasid in our reserved pages machine mask.
		 * This is used in the event of module reload.
		 */
		xpc_mach_nasids[l] |= nasid_mask_long;

		/* locate the nasid(s) which sent interrupts */

		do {
			n_IRQs_detected++;
			nasid = (l * BITS_PER_LONG + b) * 2;
			dev_dbg(xpc_part, "interrupt from nasid %lld\n", nasid);
			xpc_identify_activate_IRQ_req_sn2(nasid);

			b = find_next_bit(&nasid_mask_long, BITS_PER_LONG,
					  b + 1);
		} while (b < BITS_PER_LONG);
	}
	return n_IRQs_detected;
}