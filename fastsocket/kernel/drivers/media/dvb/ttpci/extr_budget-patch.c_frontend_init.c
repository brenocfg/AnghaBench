#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct budget_patch {TYPE_5__* dvb_frontend; int /*<<< orphan*/  dvb_adapter; TYPE_4__* dev; int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_7__ {int /*<<< orphan*/  set_params; } ;
struct TYPE_8__ {void* set_tone; void* diseqc_send_burst; void* diseqc_send_master_cmd; TYPE_1__ tuner_ops; } ;
struct TYPE_11__ {TYPE_2__ ops; int /*<<< orphan*/ * tuner_priv; } ;
struct TYPE_10__ {TYPE_3__* pci; } ;
struct TYPE_9__ {int subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  alps_bsru6_config ; 
 int /*<<< orphan*/  alps_bsru6_tuner_set_params ; 
 int /*<<< orphan*/  alps_bsrv2_config ; 
 int /*<<< orphan*/  alps_bsrv2_tuner_set_params ; 
 void* budget_diseqc_send_burst ; 
 void* budget_diseqc_send_master_cmd ; 
 void* budget_patch_diseqc_send_burst ; 
 void* budget_patch_diseqc_send_master_cmd ; 
 void* budget_patch_set_tone ; 
 void* budget_set_tone ; 
 void* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_5__*) ; 
 scalar_t__ dvb_register_frontend (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  grundig_29504_451_config ; 
 int /*<<< orphan*/  grundig_29504_451_tuner_set_params ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  stv0299_attach ; 
 int /*<<< orphan*/  tda8083_attach ; 
 int /*<<< orphan*/  ves1x93_attach ; 

__attribute__((used)) static void frontend_init(struct budget_patch* budget)
{
	switch(budget->dev->pci->subsystem_device) {
	case 0x0000: // Hauppauge/TT WinTV DVB-S rev1.X
	case 0x1013: // SATELCO Multimedia PCI

		// try the ALPS BSRV2 first of all
		budget->dvb_frontend = dvb_attach(ves1x93_attach, &alps_bsrv2_config, &budget->i2c_adap);
		if (budget->dvb_frontend) {
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsrv2_tuner_set_params;
			budget->dvb_frontend->ops.diseqc_send_master_cmd = budget_patch_diseqc_send_master_cmd;
			budget->dvb_frontend->ops.diseqc_send_burst = budget_patch_diseqc_send_burst;
			budget->dvb_frontend->ops.set_tone = budget_patch_set_tone;
			break;
		}

		// try the ALPS BSRU6 now
		budget->dvb_frontend = dvb_attach(stv0299_attach, &alps_bsru6_config, &budget->i2c_adap);
		if (budget->dvb_frontend) {
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsru6_tuner_set_params;
			budget->dvb_frontend->tuner_priv = &budget->i2c_adap;

			budget->dvb_frontend->ops.diseqc_send_master_cmd = budget_diseqc_send_master_cmd;
			budget->dvb_frontend->ops.diseqc_send_burst = budget_diseqc_send_burst;
			budget->dvb_frontend->ops.set_tone = budget_set_tone;
			break;
		}

		// Try the grundig 29504-451
		budget->dvb_frontend = dvb_attach(tda8083_attach, &grundig_29504_451_config, &budget->i2c_adap);
		if (budget->dvb_frontend) {
			budget->dvb_frontend->ops.tuner_ops.set_params = grundig_29504_451_tuner_set_params;
			budget->dvb_frontend->ops.diseqc_send_master_cmd = budget_diseqc_send_master_cmd;
			budget->dvb_frontend->ops.diseqc_send_burst = budget_diseqc_send_burst;
			budget->dvb_frontend->ops.set_tone = budget_set_tone;
			break;
		}
		break;
	}

	if (budget->dvb_frontend == NULL) {
		printk("dvb-ttpci: A frontend driver was not found for device [%04x:%04x] subsystem [%04x:%04x]\n",
		       budget->dev->pci->vendor,
		       budget->dev->pci->device,
		       budget->dev->pci->subsystem_vendor,
		       budget->dev->pci->subsystem_device);
	} else {
		if (dvb_register_frontend(&budget->dvb_adapter, budget->dvb_frontend)) {
			printk("budget-av: Frontend registration failed!\n");
			dvb_frontend_detach(budget->dvb_frontend);
			budget->dvb_frontend = NULL;
		}
	}
}