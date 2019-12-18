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
struct mpic {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  msi_check_device; int /*<<< orphan*/  teardown_msi_irqs; int /*<<< orphan*/  setup_msi_irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct mpic*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int mpic_msi_init_allocator (struct mpic*) ; 
 struct mpic* msi_mpic ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  u3msi_msi_check_device ; 
 int /*<<< orphan*/  u3msi_setup_msi_irqs ; 
 int /*<<< orphan*/  u3msi_teardown_msi_irqs ; 

int mpic_u3msi_init(struct mpic *mpic)
{
	int rc;

	rc = mpic_msi_init_allocator(mpic);
	if (rc) {
		pr_debug("u3msi: Error allocating bitmap!\n");
		return rc;
	}

	pr_debug("u3msi: Registering MPIC U3 MSI callbacks.\n");

	BUG_ON(msi_mpic);
	msi_mpic = mpic;

	WARN_ON(ppc_md.setup_msi_irqs);
	ppc_md.setup_msi_irqs = u3msi_setup_msi_irqs;
	ppc_md.teardown_msi_irqs = u3msi_teardown_msi_irqs;
	ppc_md.msi_check_device = u3msi_msi_check_device;

	return 0;
}