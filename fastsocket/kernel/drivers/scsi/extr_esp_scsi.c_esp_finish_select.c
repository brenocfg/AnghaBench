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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_device {size_t id; int /*<<< orphan*/  hostdata; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
struct esp_target_data {int flags; } ;
struct esp_cmd_entry {int flags; int /*<<< orphan*/  list; int /*<<< orphan*/ * sense_ptr; int /*<<< orphan*/  sense_dma; struct scsi_cmnd* cmd; } ;
struct esp {int seqreg; int ireg; scalar_t__ rev; int sreg; int /*<<< orphan*/  prev_soff; struct esp_target_data* target; struct esp_cmd_entry* active_cmd; int /*<<< orphan*/  queued_cmds; TYPE_1__* ops; scalar_t__ cmd_bytes_left; int /*<<< orphan*/ * cmd_bytes_ptr; int /*<<< orphan*/  flags; int /*<<< orphan*/  select_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_single ) (struct esp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dma_invalidate ) (struct esp*) ;scalar_t__ (* dma_error ) (struct esp*) ;} ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ ESP236 ; 
 int /*<<< orphan*/  ESP_CMD_ESEL ; 
 int ESP_CMD_FLAG_AUTOSENSE ; 
 int /*<<< orphan*/  ESP_CMD_NULL ; 
 int ESP_DIP ; 
 int /*<<< orphan*/  ESP_EVENT_CHECK_PHASE ; 
 int /*<<< orphan*/  ESP_FFLAGS ; 
 int ESP_FF_FBYTES ; 
 int /*<<< orphan*/  ESP_FLAG_DOING_SLOWCMD ; 
 int ESP_INTR_BSERV ; 
 int ESP_INTR_DC ; 
 int ESP_INTR_FDONE ; 
 int ESP_INTR_RSEL ; 
 int /*<<< orphan*/  ESP_SELECT_NONE ; 
 int /*<<< orphan*/  ESP_SSTEP ; 
 int ESP_STAT_PMASK ; 
 int ESP_STEP_VBITS ; 
 int ESP_TGT_CHECK_NEGO ; 
 int ESP_TGT_NEGO_SYNC ; 
 int ESP_TGT_NEGO_WIDE ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  esp_cmd_is_done (struct esp*,struct esp_cmd_entry*,struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  esp_event (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_flush_fifo (struct esp*) ; 
 int /*<<< orphan*/  esp_free_lun_tag (struct esp_cmd_entry*,int /*<<< orphan*/ ) ; 
 int esp_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_schedule_reset (struct esp*) ; 
 int /*<<< orphan*/  esp_unmap_dma (struct esp*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct esp*) ; 
 int /*<<< orphan*/  stub2 (struct esp*) ; 
 int /*<<< orphan*/  stub3 (struct esp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_finish_select(struct esp *esp)
{
	struct esp_cmd_entry *ent;
	struct scsi_cmnd *cmd;
	u8 orig_select_state;

	orig_select_state = esp->select_state;

	/* No longer selecting.  */
	esp->select_state = ESP_SELECT_NONE;

	esp->seqreg = esp_read8(ESP_SSTEP) & ESP_STEP_VBITS;
	ent = esp->active_cmd;
	cmd = ent->cmd;

	if (esp->ops->dma_error(esp)) {
		/* If we see a DMA error during or as a result of selection,
		 * all bets are off.
		 */
		esp_schedule_reset(esp);
		esp_cmd_is_done(esp, ent, cmd, (DID_ERROR << 16));
		return 0;
	}

	esp->ops->dma_invalidate(esp);

	if (esp->ireg == (ESP_INTR_RSEL | ESP_INTR_FDONE)) {
		struct esp_target_data *tp = &esp->target[cmd->device->id];

		/* Carefully back out of the selection attempt.  Release
		 * resources (such as DMA mapping & TAG) and reset state (such
		 * as message out and command delivery variables).
		 */
		if (!(ent->flags & ESP_CMD_FLAG_AUTOSENSE)) {
			esp_unmap_dma(esp, cmd);
			esp_free_lun_tag(ent, cmd->device->hostdata);
			tp->flags &= ~(ESP_TGT_NEGO_SYNC | ESP_TGT_NEGO_WIDE);
			esp->flags &= ~ESP_FLAG_DOING_SLOWCMD;
			esp->cmd_bytes_ptr = NULL;
			esp->cmd_bytes_left = 0;
		} else {
			esp->ops->unmap_single(esp, ent->sense_dma,
					       SCSI_SENSE_BUFFERSIZE,
					       DMA_FROM_DEVICE);
			ent->sense_ptr = NULL;
		}

		/* Now that the state is unwound properly, put back onto
		 * the issue queue.  This command is no longer active.
		 */
		list_move(&ent->list, &esp->queued_cmds);
		esp->active_cmd = NULL;

		/* Return value ignored by caller, it directly invokes
		 * esp_reconnect().
		 */
		return 0;
	}

	if (esp->ireg == ESP_INTR_DC) {
		struct scsi_device *dev = cmd->device;

		/* Disconnect.  Make sure we re-negotiate sync and
		 * wide parameters if this target starts responding
		 * again in the future.
		 */
		esp->target[dev->id].flags |= ESP_TGT_CHECK_NEGO;

		scsi_esp_cmd(esp, ESP_CMD_ESEL);
		esp_cmd_is_done(esp, ent, cmd, (DID_BAD_TARGET << 16));
		return 1;
	}

	if (esp->ireg == (ESP_INTR_FDONE | ESP_INTR_BSERV)) {
		/* Selection successful.  On pre-FAST chips we have
		 * to do a NOP and possibly clean out the FIFO.
		 */
		if (esp->rev <= ESP236) {
			int fcnt = esp_read8(ESP_FFLAGS) & ESP_FF_FBYTES;

			scsi_esp_cmd(esp, ESP_CMD_NULL);

			if (!fcnt &&
			    (!esp->prev_soff ||
			     ((esp->sreg & ESP_STAT_PMASK) != ESP_DIP)))
				esp_flush_fifo(esp);
		}

		/* If we are doing a slow command, negotiation, etc.
		 * we'll do the right thing as we transition to the
		 * next phase.
		 */
		esp_event(esp, ESP_EVENT_CHECK_PHASE);
		return 0;
	}

	printk("ESP: Unexpected selection completion ireg[%x].\n",
	       esp->ireg);
	esp_schedule_reset(esp);
	return 0;
}