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
typedef  int /*<<< orphan*/  u64 ;
struct xpc_partition_sn2 {int /*<<< orphan*/  activate_IRQ_phys_cpuid; int /*<<< orphan*/  activate_IRQ_nasid; scalar_t__ remote_amos_page_pa; } ;
struct TYPE_2__ {struct xpc_partition_sn2 sn2; } ;
struct xpc_partition {TYPE_1__ sn; } ;
struct amo {int /*<<< orphan*/  variable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FETCHOP_OR ; 
 int /*<<< orphan*/  FETCHOP_STORE_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GLOBAL_MMR_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NASID_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TO_AMO (int /*<<< orphan*/ ) ; 
 int XPC_DEACTIVATE_REQUEST_AMO_SN2 ; 
 scalar_t__ __va (scalar_t__) ; 
 int /*<<< orphan*/  cnodeid_to_nasid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sn_partition_id ; 
 int /*<<< orphan*/  xp_nofault_PIOR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xp_nofault_PIOR_target ; 
 int /*<<< orphan*/  xpc_send_activate_IRQ_sn2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_request_partition_deactivation_sn2(struct xpc_partition *part)
{
	struct xpc_partition_sn2 *part_sn2 = &part->sn.sn2;
	unsigned long irq_flags;
	struct amo *amo = (struct amo *)__va(part_sn2->remote_amos_page_pa +
					     (XPC_DEACTIVATE_REQUEST_AMO_SN2 *
					     sizeof(struct amo)));

	local_irq_save(irq_flags);

	/* set bit corresponding to our partid in remote partition's amo */
	FETCHOP_STORE_OP(TO_AMO((u64)&amo->variable), FETCHOP_OR,
			 BIT(sn_partition_id));

	/*
	 * We must always use the nofault function regardless of whether we
	 * are on a Shub 1.1 system or a Shub 1.2 slice 0xc processor. If we
	 * didn't, we'd never know that the other partition is down and would
	 * keep sending IRQs and amos to it until the heartbeat times out.
	 */
	(void)xp_nofault_PIOR((u64 *)GLOBAL_MMR_ADDR(NASID_GET(&amo->
							       variable),
						     xp_nofault_PIOR_target));

	local_irq_restore(irq_flags);

	/*
	 * Send activate IRQ to get other side to see that we've set our
	 * bit in their deactivate request amo.
	 */
	xpc_send_activate_IRQ_sn2(part_sn2->remote_amos_page_pa,
				  cnodeid_to_nasid(0),
				  part_sn2->activate_IRQ_nasid,
				  part_sn2->activate_IRQ_phys_cpuid);
}