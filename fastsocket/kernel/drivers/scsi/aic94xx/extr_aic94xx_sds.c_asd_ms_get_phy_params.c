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
struct asd_manuf_sec {int dummy; } ;
struct asd_manuf_phy_param {char* sig; scalar_t__ maj; int min; int num_phy_desc; int phy_desc_size; struct asd_manuf_phy_desc* phy_desc; } ;
struct asd_manuf_phy_desc {int state; int phy_id; int phy_control_0; int phy_control_1; int phy_control_2; int phy_control_3; } ;
struct TYPE_4__ {int enabled_phys; int max_phys; int num_phys; TYPE_1__* phy_desc; } ;
struct asd_ha_struct {TYPE_2__ hw_prof; } ;
struct TYPE_3__ {int phy_control_0; int phy_control_1; int phy_control_2; int phy_control_3; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,...) ; 
 int ASD_MAX_PHYS ; 
 int ENOENT ; 
#define  MS_PHY_STATE_ENABLED 130 
#define  MS_PHY_STATE_HIDDEN 129 
#define  MS_PHY_STATE_REPORTED 128 
 struct asd_manuf_phy_param* asd_find_ll_by_id (struct asd_manuf_sec*,char,char) ; 
 int /*<<< orphan*/  asd_printk (char*,scalar_t__) ; 

__attribute__((used)) static int asd_ms_get_phy_params(struct asd_ha_struct *asd_ha,
				 struct asd_manuf_sec *manuf_sec)
{
	int i;
	int en_phys = 0;
	int rep_phys = 0;
	struct asd_manuf_phy_param *phy_param;
	struct asd_manuf_phy_param dflt_phy_param;

	phy_param = asd_find_ll_by_id(manuf_sec, 'P', 'M');
	if (!phy_param) {
		ASD_DPRINTK("ms: no phy parameters found\n");
		ASD_DPRINTK("ms: Creating default phy parameters\n");
		dflt_phy_param.sig[0] = 'P';
		dflt_phy_param.sig[1] = 'M';
		dflt_phy_param.maj = 0;
		dflt_phy_param.min = 2;
		dflt_phy_param.num_phy_desc = 8;
		dflt_phy_param.phy_desc_size = sizeof(struct asd_manuf_phy_desc);
		for (i =0; i < ASD_MAX_PHYS; i++) {
			dflt_phy_param.phy_desc[i].state = 0;
			dflt_phy_param.phy_desc[i].phy_id = i;
			dflt_phy_param.phy_desc[i].phy_control_0 = 0xf6;
			dflt_phy_param.phy_desc[i].phy_control_1 = 0x10;
			dflt_phy_param.phy_desc[i].phy_control_2 = 0x43;
			dflt_phy_param.phy_desc[i].phy_control_3 = 0xeb;
		}

		phy_param = &dflt_phy_param;

	}

	if (phy_param->maj != 0) {
		asd_printk("unsupported manuf. phy param major version:0x%x\n",
			   phy_param->maj);
		return -ENOENT;
	}

	ASD_DPRINTK("ms: num_phy_desc: %d\n", phy_param->num_phy_desc);
	asd_ha->hw_prof.enabled_phys = 0;
	for (i = 0; i < phy_param->num_phy_desc; i++) {
		struct asd_manuf_phy_desc *pd = &phy_param->phy_desc[i];
		switch (pd->state & 0xF) {
		case MS_PHY_STATE_HIDDEN:
			ASD_DPRINTK("ms: phy%d: HIDDEN\n", i);
			continue;
		case MS_PHY_STATE_REPORTED:
			ASD_DPRINTK("ms: phy%d: REPORTED\n", i);
			asd_ha->hw_prof.enabled_phys &= ~(1 << i);
			rep_phys++;
			continue;
		case MS_PHY_STATE_ENABLED:
			ASD_DPRINTK("ms: phy%d: ENABLED\n", i);
			asd_ha->hw_prof.enabled_phys |= (1 << i);
			en_phys++;
			break;
		}
		asd_ha->hw_prof.phy_desc[i].phy_control_0 = pd->phy_control_0;
		asd_ha->hw_prof.phy_desc[i].phy_control_1 = pd->phy_control_1;
		asd_ha->hw_prof.phy_desc[i].phy_control_2 = pd->phy_control_2;
		asd_ha->hw_prof.phy_desc[i].phy_control_3 = pd->phy_control_3;
	}
	asd_ha->hw_prof.max_phys = rep_phys + en_phys;
	asd_ha->hw_prof.num_phys = en_phys;
	ASD_DPRINTK("ms: max_phys:0x%x, num_phys:0x%x\n",
		    asd_ha->hw_prof.max_phys, asd_ha->hw_prof.num_phys);
	ASD_DPRINTK("ms: enabled_phys:0x%x\n", asd_ha->hw_prof.enabled_phys);
	return 0;
}