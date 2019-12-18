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
struct TYPE_4__ {int have_data_in; int /*<<< orphan*/  phase; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; struct scsi_cmnd** srb; } ;
typedef  TYPE_2__ TW_Device_Extension ;

/* Variables and functions */
 int /*<<< orphan*/  TW_DRIVER ; 
 int /*<<< orphan*/  TW_PHASE_SGLIST ; 
 int /*<<< orphan*/  TW_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int scsi_dma_map (struct scsi_cmnd*) ; 

__attribute__((used)) static int twl_map_scsi_sg_data(TW_Device_Extension *tw_dev, int request_id)
{
	int use_sg;
	struct scsi_cmnd *cmd = tw_dev->srb[request_id];

	use_sg = scsi_dma_map(cmd);
	if (!use_sg)
		return 0;
	else if (use_sg < 0) {
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1, "Failed to map scatter gather list");
		return 0;
	}

	cmd->SCp.phase = TW_PHASE_SGLIST;
	cmd->SCp.have_data_in = use_sg;

	return use_sg;
}