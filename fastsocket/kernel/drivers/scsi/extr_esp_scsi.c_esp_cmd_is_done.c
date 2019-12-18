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
struct scsi_device {int id; int lun; int /*<<< orphan*/  hostdata; } ;
struct scsi_cmnd {unsigned int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/ * sense_buffer; struct scsi_device* device; } ;
struct esp_cmd_entry {int flags; int /*<<< orphan*/  list; int /*<<< orphan*/ * sense_ptr; int /*<<< orphan*/  sense_dma; int /*<<< orphan*/ * eh_done; } ;
struct esp {TYPE_2__* host; TYPE_1__* ops; int /*<<< orphan*/ * active_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  unique_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unmap_single ) (struct esp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int COMMAND_COMPLETE ; 
 int DID_OK ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int DRIVER_SENSE ; 
 int ESP_CMD_FLAG_AUTOSENSE ; 
 int ESP_DEBUG_AUTOSENSE ; 
 int SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int esp_debug ; 
 int /*<<< orphan*/  esp_free_lun_tag (struct esp_cmd_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_maybe_execute_command (struct esp*) ; 
 int /*<<< orphan*/  esp_put_ent (struct esp*,struct esp_cmd_entry*) ; 
 int /*<<< orphan*/  esp_unmap_dma (struct esp*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct esp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct scsi_cmnd*) ; 

__attribute__((used)) static void esp_cmd_is_done(struct esp *esp, struct esp_cmd_entry *ent,
			    struct scsi_cmnd *cmd, unsigned int result)
{
	struct scsi_device *dev = cmd->device;
	int tgt = dev->id;
	int lun = dev->lun;

	esp->active_cmd = NULL;
	esp_unmap_dma(esp, cmd);
	esp_free_lun_tag(ent, dev->hostdata);
	cmd->result = result;

	if (ent->eh_done) {
		complete(ent->eh_done);
		ent->eh_done = NULL;
	}

	if (ent->flags & ESP_CMD_FLAG_AUTOSENSE) {
		esp->ops->unmap_single(esp, ent->sense_dma,
				       SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
		ent->sense_ptr = NULL;

		/* Restore the message/status bytes to what we actually
		 * saw originally.  Also, report that we are providing
		 * the sense data.
		 */
		cmd->result = ((DRIVER_SENSE << 24) |
			       (DID_OK << 16) |
			       (COMMAND_COMPLETE << 8) |
			       (SAM_STAT_CHECK_CONDITION << 0));

		ent->flags &= ~ESP_CMD_FLAG_AUTOSENSE;
		if (esp_debug & ESP_DEBUG_AUTOSENSE) {
			int i;

			printk("esp%d: tgt[%d] lun[%d] AUTO SENSE[ ",
			       esp->host->unique_id, tgt, lun);
			for (i = 0; i < 18; i++)
				printk("%02x ", cmd->sense_buffer[i]);
			printk("]\n");
		}
	}

	cmd->scsi_done(cmd);

	list_del(&ent->list);
	esp_put_ent(esp, ent);

	esp_maybe_execute_command(esp);
}