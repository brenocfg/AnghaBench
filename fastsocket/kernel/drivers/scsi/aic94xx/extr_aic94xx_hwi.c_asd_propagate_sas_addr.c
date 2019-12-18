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
struct TYPE_3__ {int /*<<< orphan*/  sas_addr; TYPE_2__* phy_desc; } ;
struct asd_ha_struct {TYPE_1__ hw_prof; } ;
struct TYPE_4__ {scalar_t__* sas_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,int,int /*<<< orphan*/ ) ; 
 int ASD_MAX_PHYS ; 
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asd_propagate_sas_addr(struct asd_ha_struct *asd_ha)
{
	int i;

	for (i = 0; i < ASD_MAX_PHYS; i++) {
		if (asd_ha->hw_prof.phy_desc[i].sas_addr[0] == 0)
			continue;
		/* Set a phy's address only if it has none.
		 */
		ASD_DPRINTK("setting phy%d addr to %llx\n", i,
			    SAS_ADDR(asd_ha->hw_prof.sas_addr));
		memcpy(asd_ha->hw_prof.phy_desc[i].sas_addr,
		       asd_ha->hw_prof.sas_addr, SAS_ADDR_SIZE);
	}
}