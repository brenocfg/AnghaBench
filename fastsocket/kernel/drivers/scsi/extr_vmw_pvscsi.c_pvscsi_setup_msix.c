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
struct pvscsi_adapter {int /*<<< orphan*/  dev; } ;
struct msix_entry {unsigned int vector; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_VECTOR_COMPLETION ; 
 int pci_enable_msix (int /*<<< orphan*/ ,struct msix_entry*,int) ; 

__attribute__((used)) static int pvscsi_setup_msix(const struct pvscsi_adapter *adapter,
			     unsigned int *irq)
{
	struct msix_entry entry = { 0, PVSCSI_VECTOR_COMPLETION };
	int ret;

	ret = pci_enable_msix(adapter->dev, &entry, 1);
	if (ret)
		return ret;

	*irq = entry.vector;

	return 0;
}