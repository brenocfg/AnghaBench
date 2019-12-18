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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int enabled_phys; TYPE_1__* phy_desc; } ;
struct asd_ha_struct {TYPE_2__ hw_prof; } ;
struct asd_ctrla_phy_settings {int num_phys; struct asd_ctrla_phy_entry* phy_ent; } ;
struct asd_ctrla_phy_entry {int sas_link_rates; int sata_link_rates; int /*<<< orphan*/  flags; scalar_t__ sas_addr; } ;
struct TYPE_3__ {int max_sas_lrate; int min_sas_lrate; int max_sata_lrate; int min_sata_lrate; int /*<<< orphan*/  flags; int /*<<< orphan*/  sas_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_ENABLED (struct asd_ha_struct*,int) ; 
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_process_ctrla_phy_settings(struct asd_ha_struct *asd_ha,
					  struct asd_ctrla_phy_settings *ps)
{
	int i;
	for (i = 0; i < ps->num_phys; i++) {
		struct asd_ctrla_phy_entry *pe = &ps->phy_ent[i];

		if (!PHY_ENABLED(asd_ha, i))
			continue;
		if (*(u64 *)pe->sas_addr == 0) {
			asd_ha->hw_prof.enabled_phys &= ~(1 << i);
			continue;
		}
		/* This is the SAS address which should be sent in IDENTIFY. */
		memcpy(asd_ha->hw_prof.phy_desc[i].sas_addr, pe->sas_addr,
		       SAS_ADDR_SIZE);
		asd_ha->hw_prof.phy_desc[i].max_sas_lrate =
			(pe->sas_link_rates & 0xF0) >> 4;
		asd_ha->hw_prof.phy_desc[i].min_sas_lrate =
			(pe->sas_link_rates & 0x0F);
		asd_ha->hw_prof.phy_desc[i].max_sata_lrate =
			(pe->sata_link_rates & 0xF0) >> 4;
		asd_ha->hw_prof.phy_desc[i].min_sata_lrate =
			(pe->sata_link_rates & 0x0F);
		asd_ha->hw_prof.phy_desc[i].flags = pe->flags;
		ASD_DPRINTK("ctrla: phy%d: sas_addr: %llx, sas rate:0x%x-0x%x,"
			    " sata rate:0x%x-0x%x, flags:0x%x\n",
			    i,
			    SAS_ADDR(asd_ha->hw_prof.phy_desc[i].sas_addr),
			    asd_ha->hw_prof.phy_desc[i].max_sas_lrate,
			    asd_ha->hw_prof.phy_desc[i].min_sas_lrate,
			    asd_ha->hw_prof.phy_desc[i].max_sata_lrate,
			    asd_ha->hw_prof.phy_desc[i].min_sata_lrate,
			    asd_ha->hw_prof.phy_desc[i].flags);
	}

	return 0;
}