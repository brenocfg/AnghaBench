#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  maddr; } ;
typedef  TYPE_1__ xmaddr_t ;
typedef  int /*<<< orphan*/  u64 ;
struct desc_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DESC_LDT 129 
#define  DESC_TSS 128 
 int /*<<< orphan*/  HYPERVISOR_update_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ arbitrary_virt_to_machine (struct desc_struct*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  xen_mc_flush () ; 

__attribute__((used)) static void xen_write_gdt_entry(struct desc_struct *dt, int entry,
				const void *desc, int type)
{
	preempt_disable();

	switch (type) {
	case DESC_LDT:
	case DESC_TSS:
		/* ignore */
		break;

	default: {
		xmaddr_t maddr = arbitrary_virt_to_machine(&dt[entry]);

		xen_mc_flush();
		if (HYPERVISOR_update_descriptor(maddr.maddr, *(u64 *)desc))
			BUG();
	}

	}

	preempt_enable();
}