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
typedef  size_t u32 ;
struct sci_sas_address {scalar_t__ low; scalar_t__ high; } ;
struct isci_port {scalar_t__* phy_table; } ;

/* Variables and functions */
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  sci_phy_get_sas_address (scalar_t__,struct sci_sas_address*) ; 

void sci_port_get_sas_address(struct isci_port *iport, struct sci_sas_address *sas)
{
	u32 index;

	sas->high = 0;
	sas->low  = 0;
	for (index = 0; index < SCI_MAX_PHYS; index++)
		if (iport->phy_table[index])
			sci_phy_get_sas_address(iport->phy_table[index], sas);
}