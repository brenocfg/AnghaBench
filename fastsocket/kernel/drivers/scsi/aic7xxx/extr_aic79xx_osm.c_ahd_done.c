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
typedef  scalar_t__ uint32_t ;
typedef  size_t u_int ;
struct scsi_cmnd {int result; scalar_t__ underflow; size_t cmd_len; int* cmnd; int /*<<< orphan*/  device; scalar_t__* sense_buffer; } ;
struct scb {int flags; struct scsi_cmnd* io_ctx; TYPE_1__* platform_data; } ;
struct ahd_softc {TYPE_2__* platform_data; } ;
struct ahd_linux_device {scalar_t__ active; int openings; scalar_t__ tag_success_count; scalar_t__ maxtags; scalar_t__ commands_since_idle_or_otag; int /*<<< orphan*/  qfrozen; } ;
struct TYPE_4__ {scalar_t__ eh_done; } ;
struct TYPE_3__ {struct ahd_linux_device* dev; } ;

/* Variables and functions */
 int AHD_SHOW_MISC ; 
 scalar_t__ AHD_TAG_SUCCESS_INTERVAL ; 
 scalar_t__ CAM_BDR_SENT ; 
 scalar_t__ CAM_CMD_TIMEOUT ; 
 scalar_t__ CAM_DATA_RUN_ERR ; 
 int CAM_DEV_QFRZN ; 
 scalar_t__ CAM_REQ_ABORTED ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_REQ_INPROG ; 
 scalar_t__ CAM_SCSI_STATUS_ERROR ; 
 scalar_t__ CAM_UNCOR_PARITY ; 
 int /*<<< orphan*/  LIST_REMOVE (struct scb*,int /*<<< orphan*/ ) ; 
 int SCB_ACTIVE ; 
 int SCB_GET_TAG (struct scb*) ; 
 int SCB_RECOVERY_SCB ; 
 int SCB_TRANSMISSION_ERROR ; 
 scalar_t__ SCSI_STATUS_QUEUE_FULL ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_free_scb (struct ahd_softc*,struct scb*) ; 
 scalar_t__ ahd_get_residual (struct scb*) ; 
 scalar_t__ ahd_get_scsi_status (struct scb*) ; 
 scalar_t__ ahd_get_transaction_status (struct scb*) ; 
 scalar_t__ ahd_get_transfer_length (struct scb*) ; 
 int /*<<< orphan*/  ahd_linux_handle_scsi_status (struct ahd_softc*,int /*<<< orphan*/ ,struct scb*) ; 
 int /*<<< orphan*/  ahd_linux_queue_cmd_complete (struct ahd_softc*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ahd_linux_unmap_scb (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_print_path (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_set_transaction_status (struct scb*,scalar_t__) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pending_links ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
ahd_done(struct ahd_softc *ahd, struct scb *scb)
{
	struct scsi_cmnd *cmd;
	struct	  ahd_linux_device *dev;

	if ((scb->flags & SCB_ACTIVE) == 0) {
		printf("SCB %d done'd twice\n", SCB_GET_TAG(scb));
		ahd_dump_card_state(ahd);
		panic("Stopping for safety");
	}
	LIST_REMOVE(scb, pending_links);
	cmd = scb->io_ctx;
	dev = scb->platform_data->dev;
	dev->active--;
	dev->openings++;
	if ((cmd->result & (CAM_DEV_QFRZN << 16)) != 0) {
		cmd->result &= ~(CAM_DEV_QFRZN << 16);
		dev->qfrozen--;
	}
	ahd_linux_unmap_scb(ahd, scb);

	/*
	 * Guard against stale sense data.
	 * The Linux mid-layer assumes that sense
	 * was retrieved anytime the first byte of
	 * the sense buffer looks "sane".
	 */
	cmd->sense_buffer[0] = 0;
	if (ahd_get_transaction_status(scb) == CAM_REQ_INPROG) {
		uint32_t amount_xferred;

		amount_xferred =
		    ahd_get_transfer_length(scb) - ahd_get_residual(scb);
		if ((scb->flags & SCB_TRANSMISSION_ERROR) != 0) {
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MISC) != 0) {
				ahd_print_path(ahd, scb);
				printf("Set CAM_UNCOR_PARITY\n");
			}
#endif
			ahd_set_transaction_status(scb, CAM_UNCOR_PARITY);
#ifdef AHD_REPORT_UNDERFLOWS
		/*
		 * This code is disabled by default as some
		 * clients of the SCSI system do not properly
		 * initialize the underflow parameter.  This
		 * results in spurious termination of commands
		 * that complete as expected (e.g. underflow is
		 * allowed as command can return variable amounts
		 * of data.
		 */
		} else if (amount_xferred < scb->io_ctx->underflow) {
			u_int i;

			ahd_print_path(ahd, scb);
			printf("CDB:");
			for (i = 0; i < scb->io_ctx->cmd_len; i++)
				printf(" 0x%x", scb->io_ctx->cmnd[i]);
			printf("\n");
			ahd_print_path(ahd, scb);
			printf("Saw underflow (%ld of %ld bytes). "
			       "Treated as error\n",
				ahd_get_residual(scb),
				ahd_get_transfer_length(scb));
			ahd_set_transaction_status(scb, CAM_DATA_RUN_ERR);
#endif
		} else {
			ahd_set_transaction_status(scb, CAM_REQ_CMP);
		}
	} else if (ahd_get_transaction_status(scb) == CAM_SCSI_STATUS_ERROR) {
		ahd_linux_handle_scsi_status(ahd, cmd->device, scb);
	}

	if (dev->openings == 1
	 && ahd_get_transaction_status(scb) == CAM_REQ_CMP
	 && ahd_get_scsi_status(scb) != SCSI_STATUS_QUEUE_FULL)
		dev->tag_success_count++;
	/*
	 * Some devices deal with temporary internal resource
	 * shortages by returning queue full.  When the queue
	 * full occurrs, we throttle back.  Slowly try to get
	 * back to our previous queue depth.
	 */
	if ((dev->openings + dev->active) < dev->maxtags
	 && dev->tag_success_count > AHD_TAG_SUCCESS_INTERVAL) {
		dev->tag_success_count = 0;
		dev->openings++;
	}

	if (dev->active == 0)
		dev->commands_since_idle_or_otag = 0;

	if ((scb->flags & SCB_RECOVERY_SCB) != 0) {
		printf("Recovery SCB completes\n");
		if (ahd_get_transaction_status(scb) == CAM_BDR_SENT
		 || ahd_get_transaction_status(scb) == CAM_REQ_ABORTED)
			ahd_set_transaction_status(scb, CAM_CMD_TIMEOUT);

		if (ahd->platform_data->eh_done)
			complete(ahd->platform_data->eh_done);
	}

	ahd_free_scb(ahd, scb);
	ahd_linux_queue_cmd_complete(ahd, cmd);
}