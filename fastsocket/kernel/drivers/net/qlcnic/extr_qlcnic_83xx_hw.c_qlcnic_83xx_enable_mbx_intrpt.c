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
typedef  int u32 ;
struct qlcnic_adapter {int flags; TYPE_1__* ahw; } ;
struct TYPE_2__ {int num_msix; } ;

/* Variables and functions */
 int BIT_2 ; 
 int /*<<< orphan*/  QLCNIC_MBX_INTR_ENBL ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  QLCWRX (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_legacy_msix_mbx_intr (struct qlcnic_adapter*) ; 

void qlcnic_83xx_enable_mbx_intrpt(struct qlcnic_adapter *adapter)
{
	u32 val;

	if (adapter->flags & QLCNIC_MSIX_ENABLED)
		val = BIT_2 | ((adapter->ahw->num_msix - 1) << 8);
	else
		val = BIT_2;

	QLCWRX(adapter->ahw, QLCNIC_MBX_INTR_ENBL, val);
	qlcnic_83xx_enable_legacy_msix_mbx_intr(adapter);
}