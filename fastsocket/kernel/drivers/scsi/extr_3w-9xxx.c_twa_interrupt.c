#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_18__ ;

/* Type definitions */
typedef  int u32 ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_25__ {scalar_t__ status; TYPE_1__* sg_list; } ;
struct TYPE_26__ {TYPE_2__ newcommand; } ;
struct TYPE_29__ {TYPE_3__ command; } ;
struct TYPE_28__ {scalar_t__* state; scalar_t__ pending_request_count; int* pending_queue; size_t pending_head; int chrdev_request_id; TYPE_18__* host; struct scsi_cmnd** srb; int /*<<< orphan*/  posted_request_count; int /*<<< orphan*/  ioctl_wqueue; TYPE_6__** command_packet_virt; int /*<<< orphan*/  flags; } ;
struct TYPE_27__ {int /*<<< orphan*/  response_id; void* value; } ;
struct TYPE_24__ {scalar_t__ length; } ;
struct TYPE_23__ {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_4__ TW_Response_Queue ;
typedef  TYPE_5__ TW_Device_Extension ;
typedef  TYPE_6__ TW_Command_Full ;

/* Variables and functions */
 int CHECK_CONDITION ; 
 int DID_OK ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  TW_CLEAR_ALL_INTERRUPTS (TYPE_5__*) ; 
 int /*<<< orphan*/  TW_CLEAR_ATTENTION_INTERRUPT (TYPE_5__*) ; 
 int /*<<< orphan*/  TW_CLEAR_HOST_INTERRUPT (TYPE_5__*) ; 
 int /*<<< orphan*/  TW_DRIVER ; 
 int /*<<< orphan*/  TW_IN_ATTENTION_LOOP ; 
 int /*<<< orphan*/  TW_IN_RESET ; 
 int TW_IOCTL_CHRDEV_FREE ; 
 int /*<<< orphan*/  TW_MASK_COMMAND_INTERRUPT (TYPE_5__*) ; 
 int /*<<< orphan*/  TW_PRINTK (TYPE_18__*,int /*<<< orphan*/ ,int,char*) ; 
 int TW_Q_LENGTH ; 
 int TW_RESID_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_RESPONSE_QUEUE_REG_ADDR (TYPE_5__*) ; 
 int TW_STATUS_ATTENTION_INTERRUPT ; 
 int TW_STATUS_COMMAND_INTERRUPT ; 
 int TW_STATUS_HOST_INTERRUPT ; 
 int /*<<< orphan*/  TW_STATUS_REG_ADDR (TYPE_5__*) ; 
 int TW_STATUS_RESPONSE_INTERRUPT ; 
 int TW_STATUS_RESPONSE_QUEUE_EMPTY ; 
 int TW_STATUS_VALID_INTERRUPT ; 
 void* TW_S_COMPLETED ; 
 scalar_t__ TW_S_PENDING ; 
 scalar_t__ TW_S_POSTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* readl (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,scalar_t__) ; 
 int scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ twa_aen_complete (TYPE_5__*,int) ; 
 int twa_aen_read_queue (TYPE_5__*,int) ; 
 scalar_t__ twa_check_bits (int) ; 
 scalar_t__ twa_decode_bits (TYPE_5__*,int) ; 
 int twa_fill_sense (TYPE_5__*,int,int,int) ; 
 int /*<<< orphan*/  twa_free_request_id (TYPE_5__*,int) ; 
 int /*<<< orphan*/  twa_get_request_id (TYPE_5__*,int*) ; 
 scalar_t__ twa_post_command_packet (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  twa_scsiop_execute_scsi_complete (TYPE_5__*,int) ; 
 int /*<<< orphan*/  twa_unmap_scsi_data (TYPE_5__*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t twa_interrupt(int irq, void *dev_instance)
{
	int request_id, error = 0;
	u32 status_reg_value;
	TW_Response_Queue response_que;
	TW_Command_Full *full_command_packet;
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)dev_instance;
	int handled = 0;

	/* Get the per adapter lock */
	spin_lock(tw_dev->host->host_lock);

	/* Read the registers */
	status_reg_value = readl(TW_STATUS_REG_ADDR(tw_dev));

	/* Check if this is our interrupt, otherwise bail */
	if (!(status_reg_value & TW_STATUS_VALID_INTERRUPT))
		goto twa_interrupt_bail;

	handled = 1;

	/* If we are resetting, bail */
	if (test_bit(TW_IN_RESET, &tw_dev->flags))
		goto twa_interrupt_bail;

	/* Check controller for errors */
	if (twa_check_bits(status_reg_value)) {
		if (twa_decode_bits(tw_dev, status_reg_value)) {
			TW_CLEAR_ALL_INTERRUPTS(tw_dev);
			goto twa_interrupt_bail;
		}
	}

	/* Handle host interrupt */
	if (status_reg_value & TW_STATUS_HOST_INTERRUPT)
		TW_CLEAR_HOST_INTERRUPT(tw_dev);

	/* Handle attention interrupt */
	if (status_reg_value & TW_STATUS_ATTENTION_INTERRUPT) {
		TW_CLEAR_ATTENTION_INTERRUPT(tw_dev);
		if (!(test_and_set_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags))) {
			twa_get_request_id(tw_dev, &request_id);

			error = twa_aen_read_queue(tw_dev, request_id);
			if (error) {
				tw_dev->state[request_id] = TW_S_COMPLETED;
				twa_free_request_id(tw_dev, request_id);
				clear_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags);
			}
		}
	}

	/* Handle command interrupt */
	if (status_reg_value & TW_STATUS_COMMAND_INTERRUPT) {
		TW_MASK_COMMAND_INTERRUPT(tw_dev);
		/* Drain as many pending commands as we can */
		while (tw_dev->pending_request_count > 0) {
			request_id = tw_dev->pending_queue[tw_dev->pending_head];
			if (tw_dev->state[request_id] != TW_S_PENDING) {
				TW_PRINTK(tw_dev->host, TW_DRIVER, 0x19, "Found request id that wasn't pending");
				TW_CLEAR_ALL_INTERRUPTS(tw_dev);
				goto twa_interrupt_bail;
			}
			if (twa_post_command_packet(tw_dev, request_id, 1)==0) {
				tw_dev->pending_head = (tw_dev->pending_head + 1) % TW_Q_LENGTH;
				tw_dev->pending_request_count--;
			} else {
				/* If we get here, we will continue re-posting on the next command interrupt */
				break;
			}
		}
	}

	/* Handle response interrupt */
	if (status_reg_value & TW_STATUS_RESPONSE_INTERRUPT) {

		/* Drain the response queue from the board */
		while ((status_reg_value & TW_STATUS_RESPONSE_QUEUE_EMPTY) == 0) {
			/* Complete the response */
			response_que.value = readl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
			request_id = TW_RESID_OUT(response_que.response_id);
			full_command_packet = tw_dev->command_packet_virt[request_id];
			error = 0;
			/* Check for command packet errors */
			if (full_command_packet->command.newcommand.status != 0) {
				if (tw_dev->srb[request_id] != NULL) {
					error = twa_fill_sense(tw_dev, request_id, 1, 1);
				} else {
					/* Skip ioctl error prints */
					if (request_id != tw_dev->chrdev_request_id) {
						error = twa_fill_sense(tw_dev, request_id, 0, 1);
					}
				}
			}

			/* Check for correct state */
			if (tw_dev->state[request_id] != TW_S_POSTED) {
				if (tw_dev->srb[request_id] != NULL) {
					TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1a, "Received a request id that wasn't posted");
					TW_CLEAR_ALL_INTERRUPTS(tw_dev);
					goto twa_interrupt_bail;
				}
			}

			/* Check for internal command completion */
			if (tw_dev->srb[request_id] == NULL) {
				if (request_id != tw_dev->chrdev_request_id) {
					if (twa_aen_complete(tw_dev, request_id))
						TW_PRINTK(tw_dev->host, TW_DRIVER, 0x1b, "Error completing AEN during attention interrupt");
				} else {
					tw_dev->chrdev_request_id = TW_IOCTL_CHRDEV_FREE;
					wake_up(&tw_dev->ioctl_wqueue);
				}
			} else {
				struct scsi_cmnd *cmd;

				cmd = tw_dev->srb[request_id];

				twa_scsiop_execute_scsi_complete(tw_dev, request_id);
				/* If no error command was a success */
				if (error == 0) {
					cmd->result = (DID_OK << 16);
				}

				/* If error, command failed */
				if (error == 1) {
					/* Ask for a host reset */
					cmd->result = (DID_OK << 16) | (CHECK_CONDITION << 1);
				}

				/* Report residual bytes for single sgl */
				if ((scsi_sg_count(cmd) <= 1) && (full_command_packet->command.newcommand.status == 0)) {
					if (full_command_packet->command.newcommand.sg_list[0].length < scsi_bufflen(tw_dev->srb[request_id]))
						scsi_set_resid(cmd, scsi_bufflen(cmd) - full_command_packet->command.newcommand.sg_list[0].length);
				}

				/* Now complete the io */
				tw_dev->state[request_id] = TW_S_COMPLETED;
				twa_free_request_id(tw_dev, request_id);
				tw_dev->posted_request_count--;
				tw_dev->srb[request_id]->scsi_done(tw_dev->srb[request_id]);
				twa_unmap_scsi_data(tw_dev, request_id);
			}

			/* Check for valid status after each drain */
			status_reg_value = readl(TW_STATUS_REG_ADDR(tw_dev));
			if (twa_check_bits(status_reg_value)) {
				if (twa_decode_bits(tw_dev, status_reg_value)) {
					TW_CLEAR_ALL_INTERRUPTS(tw_dev);
					goto twa_interrupt_bail;
				}
			}
		}
	}

twa_interrupt_bail:
	spin_unlock(tw_dev->host->host_lock);
	return IRQ_RETVAL(handled);
}