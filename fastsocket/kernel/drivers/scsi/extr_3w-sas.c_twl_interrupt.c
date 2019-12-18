#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int dma_addr_t ;
struct TYPE_23__ {scalar_t__ status; TYPE_2__* sg_list; } ;
struct TYPE_24__ {TYPE_3__ newcommand; } ;
struct TYPE_26__ {TYPE_4__ command; } ;
struct TYPE_25__ {int* sense_buffer_phys; int chrdev_request_id; scalar_t__* state; TYPE_14__* host; struct scsi_cmnd** srb; int /*<<< orphan*/  posted_request_count; int /*<<< orphan*/  ioctl_wqueue; TYPE_6__** command_packet_virt; TYPE_13__** sense_buffer_virt; int /*<<< orphan*/  flags; } ;
struct TYPE_22__ {scalar_t__ length; } ;
struct TYPE_21__ {int /*<<< orphan*/  request_id; } ;
struct TYPE_20__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_19__ {TYPE_1__ header_desc; } ;
typedef  TYPE_5__ TW_Device_Extension ;
typedef  TYPE_6__ TW_Command_Full ;
typedef  int /*<<< orphan*/  TW_Command_Apache_Header ;

/* Variables and functions */
 int DID_OK ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int TWL_HISTATUS_ATTENTION_INTERRUPT ; 
 int TWL_HISTATUS_RESPONSE_INTERRUPT ; 
 int TWL_HISTATUS_VALID_INTERRUPT ; 
 int /*<<< orphan*/  TWL_HISTAT_REG_ADDR (TYPE_5__*) ; 
 int /*<<< orphan*/  TWL_HOBQPH_REG_ADDR (TYPE_5__*) ; 
 int /*<<< orphan*/  TWL_HOBQPL_REG_ADDR (TYPE_5__*) ; 
 int /*<<< orphan*/  TWL_MASK_INTERRUPTS (TYPE_5__*) ; 
 int /*<<< orphan*/  TW_DRIVER ; 
 int /*<<< orphan*/  TW_IN_RESET ; 
 int TW_IOCTL_CHRDEV_FREE ; 
 int /*<<< orphan*/  TW_NOTMFA_OUT (int) ; 
 int /*<<< orphan*/  TW_PRINTK (TYPE_14__*,int /*<<< orphan*/ ,int,char*) ; 
 int TW_Q_LENGTH ; 
 int TW_RESID_OUT (int) ; 
 scalar_t__ TW_S_COMPLETED ; 
 scalar_t__ TW_S_POSTED ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_13__*,int) ; 
 void* readl (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,scalar_t__) ; 
 int scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ twl_aen_complete (TYPE_5__*,int) ; 
 int twl_fill_sense (TYPE_5__*,int,int,int,int) ; 
 int /*<<< orphan*/  twl_free_request_id (TYPE_5__*,int) ; 
 scalar_t__ twl_handle_attention_interrupt (TYPE_5__*) ; 
 int /*<<< orphan*/  twl_unmap_scsi_data (TYPE_5__*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t twl_interrupt(int irq, void *dev_instance)
{
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)dev_instance;
	int i, handled = 0, error = 0;
	dma_addr_t mfa = 0;
	u32 reg, regl, regh, response, request_id = 0;
	struct scsi_cmnd *cmd;
	TW_Command_Full *full_command_packet;

	spin_lock(tw_dev->host->host_lock);

	/* Read host interrupt status */
	reg = readl(TWL_HISTAT_REG_ADDR(tw_dev));

	/* Check if this is our interrupt, otherwise bail */
	if (!(reg & TWL_HISTATUS_VALID_INTERRUPT))
		goto twl_interrupt_bail;

	handled = 1;

	/* If we are resetting, bail */
	if (test_bit(TW_IN_RESET, &tw_dev->flags))
		goto twl_interrupt_bail;

	/* Attention interrupt */
	if (reg & TWL_HISTATUS_ATTENTION_INTERRUPT) {
		if (twl_handle_attention_interrupt(tw_dev)) {
			TWL_MASK_INTERRUPTS(tw_dev);
			goto twl_interrupt_bail;
		}
	}

	/* Response interrupt */
	while (reg & TWL_HISTATUS_RESPONSE_INTERRUPT) {
		if (sizeof(dma_addr_t) > 4) {
			regh = readl(TWL_HOBQPH_REG_ADDR(tw_dev));
			regl = readl(TWL_HOBQPL_REG_ADDR(tw_dev));
			mfa = ((u64)regh << 32) | regl;
		} else
			mfa = readl(TWL_HOBQPL_REG_ADDR(tw_dev));

		error = 0;
		response = (u32)mfa;

		/* Check for command packet error */
		if (!TW_NOTMFA_OUT(response)) {
			for (i=0;i<TW_Q_LENGTH;i++) {
				if (tw_dev->sense_buffer_phys[i] == mfa) {
					request_id = le16_to_cpu(tw_dev->sense_buffer_virt[i]->header_desc.request_id);
					if (tw_dev->srb[request_id] != NULL)
						error = twl_fill_sense(tw_dev, i, request_id, 1, 1);
					else {
						/* Skip ioctl error prints */
						if (request_id != tw_dev->chrdev_request_id)
							error = twl_fill_sense(tw_dev, i, request_id, 0, 1);
						else
							memcpy(tw_dev->command_packet_virt[request_id], tw_dev->sense_buffer_virt[i], sizeof(TW_Command_Apache_Header));
					}

					/* Now re-post the sense buffer */
					writel((u32)((u64)tw_dev->sense_buffer_phys[i] >> 32), TWL_HOBQPH_REG_ADDR(tw_dev));
					writel((u32)tw_dev->sense_buffer_phys[i], TWL_HOBQPL_REG_ADDR(tw_dev));
					break;
				}
			}
		} else
			request_id = TW_RESID_OUT(response);

		full_command_packet = tw_dev->command_packet_virt[request_id];

		/* Check for correct state */
		if (tw_dev->state[request_id] != TW_S_POSTED) {
			if (tw_dev->srb[request_id] != NULL) {
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0xe, "Received a request id that wasn't posted");
				TWL_MASK_INTERRUPTS(tw_dev);
				goto twl_interrupt_bail;
			}
		}

		/* Check for internal command completion */
		if (tw_dev->srb[request_id] == NULL) {
			if (request_id != tw_dev->chrdev_request_id) {
				if (twl_aen_complete(tw_dev, request_id))
					TW_PRINTK(tw_dev->host, TW_DRIVER, 0xf, "Error completing AEN during attention interrupt");
			} else {
				tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;
				wake_up(&tw_dev->ioctl_wqueue);
			}
		} else {
			cmd = tw_dev->srb[request_id];

			if (!error)
				cmd->result = (DID_OK << 16);

			/* Report residual bytes for single sgl */
			if ((scsi_sg_count(cmd) <= 1) && (full_command_packet->command.newcommand.status == 0)) {
				if (full_command_packet->command.newcommand.sg_list[0].length < scsi_bufflen(tw_dev->srb[request_id]))
					scsi_set_resid(cmd, scsi_bufflen(cmd) - full_command_packet->command.newcommand.sg_list[0].length);
			}

			/* Now complete the io */
			tw_dev->state[request_id] = TW_S_COMPLETED;
			twl_free_request_id(tw_dev, request_id);
			tw_dev->posted_request_count--;
			tw_dev->srb[request_id]->scsi_done(tw_dev->srb[request_id]);
			twl_unmap_scsi_data(tw_dev, request_id);
		}

		/* Check for another response interrupt */
		reg = readl(TWL_HISTAT_REG_ADDR(tw_dev));
	}

twl_interrupt_bail:
	spin_unlock(tw_dev->host->host_lock);
	return IRQ_RETVAL(handled);
}