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
struct isci_port {int /*<<< orphan*/ ** phy_table; } ;

/* Variables and functions */
 size_t SCI_MAX_PHYS ; 

__attribute__((used)) static bool sci_port_is_wide(struct isci_port *iport)
{
	u32 index;
	u32 phy_count = 0;

	for (index = 0; index < SCI_MAX_PHYS; index++) {
		if (iport->phy_table[index] != NULL) {
			phy_count++;
		}
	}

	return phy_count != 1;
}