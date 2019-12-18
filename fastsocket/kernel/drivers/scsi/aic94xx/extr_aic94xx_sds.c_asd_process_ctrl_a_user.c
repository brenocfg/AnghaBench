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
typedef  int u32 ;
struct asd_ll_el {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sas_addr; } ;
struct asd_ha_struct {TYPE_1__ hw_prof; } ;
struct asd_flash_dir {int dummy; } ;
struct asd_ctrla_phy_settings {char id0; int num_phys; TYPE_2__* phy_ent; } ;
struct TYPE_4__ {int sas_link_rates; int flags; int sata_link_rates; int /*<<< orphan*/  sas_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*) ; 
 int ASD_MAX_PHYS ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLASH_DE_CTRL_A_USER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int asd_find_flash_de (struct asd_flash_dir*,int /*<<< orphan*/ ,int*,int*) ; 
 struct asd_ctrla_phy_settings* asd_find_ll_by_id (struct asd_ll_el*,char,int) ; 
 int asd_process_ctrla_phy_settings (struct asd_ha_struct*,struct asd_ctrla_phy_settings*) ; 
 int asd_read_flash_seg (struct asd_ha_struct*,void*,int,int) ; 
 int /*<<< orphan*/  kfree (struct asd_ll_el*) ; 
 struct asd_ll_el* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_process_ctrl_a_user(struct asd_ha_struct *asd_ha,
				   struct asd_flash_dir *flash_dir)
{
	int err, i;
	u32 offs, size;
	struct asd_ll_el *el;
	struct asd_ctrla_phy_settings *ps;
	struct asd_ctrla_phy_settings dflt_ps;

	err = asd_find_flash_de(flash_dir, FLASH_DE_CTRL_A_USER, &offs, &size);
	if (err) {
		ASD_DPRINTK("couldn't find CTRL-A user settings section\n");
		ASD_DPRINTK("Creating default CTRL-A user settings section\n");

		dflt_ps.id0 = 'h';
		dflt_ps.num_phys = 8;
		for (i =0; i < ASD_MAX_PHYS; i++) {
			memcpy(dflt_ps.phy_ent[i].sas_addr,
			       asd_ha->hw_prof.sas_addr, SAS_ADDR_SIZE);
			dflt_ps.phy_ent[i].sas_link_rates = 0x98;
			dflt_ps.phy_ent[i].flags = 0x0;
			dflt_ps.phy_ent[i].sata_link_rates = 0x0;
		}

		size = sizeof(struct asd_ctrla_phy_settings);
		ps = &dflt_ps;
	}

	if (size == 0)
		goto out;

	err = -ENOMEM;
	el = kmalloc(size, GFP_KERNEL);
	if (!el) {
		ASD_DPRINTK("no mem for ctrla user settings section\n");
		goto out;
	}

	err = asd_read_flash_seg(asd_ha, (void *)el, offs, size);
	if (err) {
		ASD_DPRINTK("couldn't read ctrla phy settings section\n");
		goto out2;
	}

	err = -ENOENT;
	ps = asd_find_ll_by_id(el, 'h', 0xFF);
	if (!ps) {
		ASD_DPRINTK("couldn't find ctrla phy settings struct\n");
		goto out2;
	}

	err = asd_process_ctrla_phy_settings(asd_ha, ps);
	if (err) {
		ASD_DPRINTK("couldn't process ctrla phy settings\n");
		goto out2;
	}
out2:
	kfree(el);
out:
	return err;
}