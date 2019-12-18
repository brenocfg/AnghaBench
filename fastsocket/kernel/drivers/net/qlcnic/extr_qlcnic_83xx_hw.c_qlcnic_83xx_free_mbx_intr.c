#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct qlcnic_adapter {int flags; TYPE_2__* msix_entries; TYPE_1__* ahw; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {size_t num_msix; } ;

/* Variables and functions */
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qlcnic_83xx_disable_mbx_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_set_legacy_intr_mask (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

void qlcnic_83xx_free_mbx_intr(struct qlcnic_adapter *adapter)
{
	u32 num_msix;

	if (!(adapter->flags & QLCNIC_MSIX_ENABLED))
		qlcnic_83xx_set_legacy_intr_mask(adapter);

	qlcnic_83xx_disable_mbx_intr(adapter);

	if (adapter->flags & QLCNIC_MSIX_ENABLED)
		num_msix = adapter->ahw->num_msix - 1;
	else
		num_msix = 0;

	msleep(20);
	synchronize_irq(adapter->msix_entries[num_msix].vector);
	free_irq(adapter->msix_entries[num_msix].vector, adapter);
}