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
struct ctlr_info {size_t intr_mode; int /*<<< orphan*/  ctlr; TYPE_1__* pdev; int /*<<< orphan*/ * intr; struct Scsi_Host* scsi_host; int /*<<< orphan*/  maxsgentries; int /*<<< orphan*/  nr_cmds; } ;
struct Scsi_Host {int this_id; int max_channel; unsigned long* hostdata; int /*<<< orphan*/  irq; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  cmd_per_lun; int /*<<< orphan*/  can_queue; void* max_id; void* max_lun; int /*<<< orphan*/  max_cmd_len; scalar_t__ n_io_port; scalar_t__ io_port; } ;
typedef  int /*<<< orphan*/  h ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* HPSA_MAX_LUN ; 
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_driver_template ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 

__attribute__((used)) static int hpsa_scsi_detect(struct ctlr_info *h)
{
	struct Scsi_Host *sh;
	int error;

	sh = scsi_host_alloc(&hpsa_driver_template, sizeof(h));
	if (sh == NULL)
		goto fail;

	sh->io_port = 0;
	sh->n_io_port = 0;
	sh->this_id = -1;
	sh->max_channel = 3;
	sh->max_cmd_len = MAX_COMMAND_SIZE;
	sh->max_lun = HPSA_MAX_LUN;
	sh->max_id = HPSA_MAX_LUN;
	sh->can_queue = h->nr_cmds;
	sh->cmd_per_lun = h->nr_cmds;
	sh->sg_tablesize = h->maxsgentries;
	h->scsi_host = sh;
	sh->hostdata[0] = (unsigned long) h;
	sh->irq = h->intr[h->intr_mode];
	sh->unique_id = sh->irq;
	error = scsi_add_host(sh, &h->pdev->dev);
	if (error)
		goto fail_host_put;
	scsi_scan_host(sh);
	return 0;

 fail_host_put:
	dev_err(&h->pdev->dev, "hpsa_scsi_detect: scsi_add_host"
		" failed for controller %d\n", h->ctlr);
	scsi_host_put(sh);
	return error;
 fail:
	dev_err(&h->pdev->dev, "hpsa_scsi_detect: scsi_host_alloc"
		" failed for controller %d\n", h->ctlr);
	return -ENOMEM;
}