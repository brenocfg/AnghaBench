#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scsi_host_template {int dummy; } ;
struct Scsi_Host {unsigned long* hostdata; int max_id; int max_lun; int cmd_per_lun; int /*<<< orphan*/  can_queue; int /*<<< orphan*/  sg_tablesize; scalar_t__ unique_id; scalar_t__ max_channel; scalar_t__ n_io_port; scalar_t__ io_port; int /*<<< orphan*/  irq; } ;
typedef  int s32 ;
struct TYPE_5__ {int /*<<< orphan*/  post_fifo_size; int /*<<< orphan*/  sg_tablesize; scalar_t__ unit; scalar_t__ top_scsi_channel; TYPE_1__* pDev; struct Scsi_Host* host; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ adpt_hba ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 scalar_t__ sys_tbl_pa ; 

__attribute__((used)) static s32 adpt_scsi_host_alloc(adpt_hba* pHba, struct scsi_host_template *sht)
{
	struct Scsi_Host *host;

	host = scsi_host_alloc(sht, sizeof(adpt_hba*));
	if (host == NULL) {
		printk("%s: scsi_host_alloc returned NULL\n", pHba->name);
		return -1;
	}
	host->hostdata[0] = (unsigned long)pHba;
	pHba->host = host;

	host->irq = pHba->pDev->irq;
	/* no IO ports, so don't have to set host->io_port and
	 * host->n_io_port
	 */
	host->io_port = 0;
	host->n_io_port = 0;
				/* see comments in scsi_host.h */
	host->max_id = 16;
	host->max_lun = 256;
	host->max_channel = pHba->top_scsi_channel + 1;
	host->cmd_per_lun = 1;
	host->unique_id = (u32)sys_tbl_pa + pHba->unit;
	host->sg_tablesize = pHba->sg_tablesize;
	host->can_queue = pHba->post_fifo_size;

	return 0;
}