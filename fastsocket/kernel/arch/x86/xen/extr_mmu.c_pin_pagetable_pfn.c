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
struct TYPE_2__ {int /*<<< orphan*/  mfn; } ;
struct mmuext_op {unsigned int cmd; TYPE_1__ arg1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 scalar_t__ HYPERVISOR_mmuext_op (struct mmuext_op*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_mfn (unsigned long) ; 

__attribute__((used)) static void pin_pagetable_pfn(unsigned cmd, unsigned long pfn)
{
	struct mmuext_op op;
	op.cmd = cmd;
	op.arg1.mfn = pfn_to_mfn(pfn);
	if (HYPERVISOR_mmuext_op(&op, 1, NULL, DOMID_SELF))
		BUG();
}