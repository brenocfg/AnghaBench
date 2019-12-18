#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* enableint ) (TYPE_6__*) ;int /*<<< orphan*/  (* statinit ) (TYPE_6__*) ;} ;
struct TYPE_22__ {int reset_count; int requires_esl; int ntargets; int nlun; int nbus; int max_xfer; int max_cmds; scalar_t__ ad_type; int* ha_id; scalar_t__* dcdb_active; TYPE_5__* conf; TYPE_3__* enq; TYPE_2__* subsys; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  last_ffdc; TYPE_1__ func; } ;
typedef  TYPE_6__ ips_ha_t ;
struct TYPE_21__ {scalar_t__ ucLogDriveCount; int* init_id; TYPE_4__* logical_drive; } ;
struct TYPE_20__ {int ucStripeSize; } ;
struct TYPE_19__ {int ucMaxPhysicalDevices; int ucConcurrentCmdCount; } ;
struct TYPE_18__ {int /*<<< orphan*/ * param; } ;

/* Variables and functions */
 int IPS_ADAPTER_ID ; 
 scalar_t__ IPS_ADTYPE_SERVERAID3L ; 
 scalar_t__ IPS_ADTYPE_SERVERAID4L ; 
 scalar_t__ IPS_ADTYPE_SERVERAID4LX ; 
 int /*<<< orphan*/  IPS_INTR_IORL ; 
 int IPS_MAX_TARGETS ; 
 int /*<<< orphan*/  IPS_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 scalar_t__ MaxLiteCmds ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  ips_clear_adapter (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_ffdc_reset (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_identify_controller (TYPE_6__*) ; 
 int /*<<< orphan*/  ips_read_adapter_status (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_read_config (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_read_subsystem_parameters (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_write_driver_status (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*) ; 

__attribute__((used)) static int
ips_hainit(ips_ha_t * ha)
{
	int i;
	struct timeval tv;

	METHOD_TRACE("ips_hainit", 1);

	if (!ha)
		return (0);

	if (ha->func.statinit)
		(*ha->func.statinit) (ha);

	if (ha->func.enableint)
		(*ha->func.enableint) (ha);

	/* Send FFDC */
	ha->reset_count = 1;
	do_gettimeofday(&tv);
	ha->last_ffdc = tv.tv_sec;
	ips_ffdc_reset(ha, IPS_INTR_IORL);

	if (!ips_read_config(ha, IPS_INTR_IORL)) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to read config from controller.\n");

		return (0);
	}
	/* end if */
	if (!ips_read_adapter_status(ha, IPS_INTR_IORL)) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to read controller status.\n");

		return (0);
	}

	/* Identify this controller */
	ips_identify_controller(ha);

	if (!ips_read_subsystem_parameters(ha, IPS_INTR_IORL)) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to read subsystem parameters.\n");

		return (0);
	}

	/* write nvram user page 5 */
	if (!ips_write_driver_status(ha, IPS_INTR_IORL)) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "unable to write driver info to controller.\n");

		return (0);
	}

	/* If there are Logical Drives and a Reset Occurred, then an EraseStripeLock is Needed */
	if ((ha->conf->ucLogDriveCount > 0) && (ha->requires_esl == 1))
		ips_clear_adapter(ha, IPS_INTR_IORL);

	/* set limits on SID, LUN, BUS */
	ha->ntargets = IPS_MAX_TARGETS + 1;
	ha->nlun = 1;
	ha->nbus = (ha->enq->ucMaxPhysicalDevices / IPS_MAX_TARGETS) + 1;

	switch (ha->conf->logical_drive[0].ucStripeSize) {
	case 4:
		ha->max_xfer = 0x10000;
		break;

	case 5:
		ha->max_xfer = 0x20000;
		break;

	case 6:
		ha->max_xfer = 0x40000;
		break;

	case 7:
	default:
		ha->max_xfer = 0x80000;
		break;
	}

	/* setup max concurrent commands */
	if (le32_to_cpu(ha->subsys->param[4]) & 0x1) {
		/* Use the new method */
		ha->max_cmds = ha->enq->ucConcurrentCmdCount;
	} else {
		/* use the old method */
		switch (ha->conf->logical_drive[0].ucStripeSize) {
		case 4:
			ha->max_cmds = 32;
			break;

		case 5:
			ha->max_cmds = 16;
			break;

		case 6:
			ha->max_cmds = 8;
			break;

		case 7:
		default:
			ha->max_cmds = 4;
			break;
		}
	}

	/* Limit the Active Commands on a Lite Adapter */
	if ((ha->ad_type == IPS_ADTYPE_SERVERAID3L) ||
	    (ha->ad_type == IPS_ADTYPE_SERVERAID4L) ||
	    (ha->ad_type == IPS_ADTYPE_SERVERAID4LX)) {
		if ((ha->max_cmds > MaxLiteCmds) && (MaxLiteCmds))
			ha->max_cmds = MaxLiteCmds;
	}

	/* set controller IDs */
	ha->ha_id[0] = IPS_ADAPTER_ID;
	for (i = 1; i < ha->nbus; i++) {
		ha->ha_id[i] = ha->conf->init_id[i - 1] & 0x1f;
		ha->dcdb_active[i - 1] = 0;
	}

	return (1);
}