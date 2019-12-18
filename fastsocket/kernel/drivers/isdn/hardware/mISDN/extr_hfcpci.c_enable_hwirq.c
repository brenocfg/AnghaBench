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
struct TYPE_2__ {int /*<<< orphan*/  int_m2; } ;
struct hfc_pci {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFCPCI_INT_M2 ; 
 int /*<<< orphan*/  HFCPCI_IRQ_ENABLE ; 
 int /*<<< orphan*/  Write_hfc (struct hfc_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_hwirq(struct hfc_pci *hc)
{
	hc->hw.int_m2 |= HFCPCI_IRQ_ENABLE;
	Write_hfc(hc, HFCPCI_INT_M2, hc->hw.int_m2);
}