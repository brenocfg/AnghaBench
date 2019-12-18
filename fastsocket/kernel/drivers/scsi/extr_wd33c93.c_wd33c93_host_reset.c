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
struct scsi_cmnd {int result; TYPE_1__* device; } ;
struct WD33C93_hostdata {scalar_t__ outgoing_len; scalar_t__ incoming_ptr; int /*<<< orphan*/  dma; int /*<<< orphan*/  state; int /*<<< orphan*/ * disconnected_Q; int /*<<< orphan*/ * connected; int /*<<< orphan*/ * selecting; int /*<<< orphan*/ * input_Q; int /*<<< orphan*/ * sync_stat; int /*<<< orphan*/  sx_table; int /*<<< orphan*/ * sync_xfer; scalar_t__* busy; int /*<<< orphan*/  (* dma_stop ) (struct Scsi_Host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct Scsi_Host {int /*<<< orphan*/  irq; int /*<<< orphan*/  host_no; scalar_t__ hostdata; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SX_OFF ; 
 int DEFAULT_SX_PER ; 
 int DID_RESET ; 
 int /*<<< orphan*/  D_DMA_OFF ; 
 int /*<<< orphan*/  SS_UNSET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  S_UNCONNECTED ; 
 int /*<<< orphan*/  calc_sync_xfer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_wd33c93 (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct Scsi_Host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
wd33c93_host_reset(struct scsi_cmnd * SCpnt)
{
	struct Scsi_Host *instance;
	struct WD33C93_hostdata *hostdata;
	int i;

	instance = SCpnt->device->host;
	hostdata = (struct WD33C93_hostdata *) instance->hostdata;

	printk("scsi%d: reset. ", instance->host_no);
	disable_irq(instance->irq);

	hostdata->dma_stop(instance, NULL, 0);
	for (i = 0; i < 8; i++) {
		hostdata->busy[i] = 0;
		hostdata->sync_xfer[i] =
			calc_sync_xfer(DEFAULT_SX_PER / 4, DEFAULT_SX_OFF,
					0, hostdata->sx_table);
		hostdata->sync_stat[i] = SS_UNSET;	/* using default sync values */
	}
	hostdata->input_Q = NULL;
	hostdata->selecting = NULL;
	hostdata->connected = NULL;
	hostdata->disconnected_Q = NULL;
	hostdata->state = S_UNCONNECTED;
	hostdata->dma = D_DMA_OFF;
	hostdata->incoming_ptr = 0;
	hostdata->outgoing_len = 0;

	reset_wd33c93(instance);
	SCpnt->result = DID_RESET << 16;
	enable_irq(instance->irq);
	return SUCCESS;
}