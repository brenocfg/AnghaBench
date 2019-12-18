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
struct sci_sas_address {int high; int low; } ;
struct isci_port {int physical_port_index; TYPE_1__* viit_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  reserved; int /*<<< orphan*/  initiator_sas_address_lo; int /*<<< orphan*/  initiator_sas_address_hi; } ;

/* Variables and functions */
 int SCU_VIIT_ENTRY_ID_VIIT ; 
 int SCU_VIIT_ENTRY_LPVIE_SHIFT ; 
 int SCU_VIIT_IPPT_INITIATOR ; 
 int SCU_VIIT_STATUS_ALL_VALID ; 
 int /*<<< orphan*/  sci_port_get_sas_address (struct isci_port*,struct sci_sas_address*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_port_update_viit_entry(struct isci_port *iport)
{
	struct sci_sas_address sas_address;

	sci_port_get_sas_address(iport, &sas_address);

	writel(sas_address.high,
		&iport->viit_registers->initiator_sas_address_hi);
	writel(sas_address.low,
		&iport->viit_registers->initiator_sas_address_lo);

	/* This value get cleared just in case its not already cleared */
	writel(0, &iport->viit_registers->reserved);

	/* We are required to update the status register last */
	writel(SCU_VIIT_ENTRY_ID_VIIT |
	       SCU_VIIT_IPPT_INITIATOR |
	       ((1 << iport->physical_port_index) << SCU_VIIT_ENTRY_LPVIE_SHIFT) |
	       SCU_VIIT_STATUS_ALL_VALID,
	       &iport->viit_registers->status);
}