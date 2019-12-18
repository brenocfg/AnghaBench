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
struct msix_entry {int dummy; } ;
struct e1000_adapter {int int_mode; int flags; int num_vectors; int /*<<< orphan*/  pdev; TYPE_1__* msix_entries; } ;
struct TYPE_3__ {int entry; } ;

/* Variables and functions */
#define  E1000E_INT_MODE_LEGACY 130 
#define  E1000E_INT_MODE_MSI 129 
#define  E1000E_INT_MODE_MSIX 128 
 int FLAG_HAS_MSIX ; 
 int FLAG_MSI_ENABLED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  e1000e_reset_interrupt_capability (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e_err (char*) ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_msi (int /*<<< orphan*/ ) ; 
 int pci_enable_msix (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void e1000e_set_interrupt_capability(struct e1000_adapter *adapter)
{
	int err;
	int i;

	switch (adapter->int_mode) {
	case E1000E_INT_MODE_MSIX:
		if (adapter->flags & FLAG_HAS_MSIX) {
			adapter->num_vectors = 3; /* RxQ0, TxQ0 and other */
			adapter->msix_entries = kcalloc(adapter->num_vectors,
						      sizeof(struct msix_entry),
						      GFP_KERNEL);
			if (adapter->msix_entries) {
				for (i = 0; i < adapter->num_vectors; i++)
					adapter->msix_entries[i].entry = i;

				err = pci_enable_msix(adapter->pdev,
						      adapter->msix_entries,
						      adapter->num_vectors);
				if (err == 0)
					return;
			}
			/* MSI-X failed, so fall through and try MSI */
			e_err("Failed to initialize MSI-X interrupts.  Falling back to MSI interrupts.\n");
			e1000e_reset_interrupt_capability(adapter);
		}
		adapter->int_mode = E1000E_INT_MODE_MSI;
		/* Fall through */
	case E1000E_INT_MODE_MSI:
		if (!pci_enable_msi(adapter->pdev)) {
			adapter->flags |= FLAG_MSI_ENABLED;
		} else {
			adapter->int_mode = E1000E_INT_MODE_LEGACY;
			e_err("Failed to initialize MSI interrupts.  Falling back to legacy interrupts.\n");
		}
		/* Fall through */
	case E1000E_INT_MODE_LEGACY:
		/* Don't do anything; this is the system default */
		break;
	}

	/* store the number of vectors being used */
	adapter->num_vectors = 1;
}