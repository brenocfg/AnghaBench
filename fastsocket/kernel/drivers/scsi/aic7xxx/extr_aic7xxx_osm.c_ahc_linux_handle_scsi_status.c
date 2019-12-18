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
typedef  int /*<<< orphan*/  u_long ;
typedef  size_t u_int ;
struct scsi_sense_data {int dummy; } ;
struct scsi_device {TYPE_1__* sdev_target; int /*<<< orphan*/  lun; } ;
struct scsi_cmnd {size_t* sense_buffer; int result; } ;
struct scb {int flags; struct scsi_cmnd* io_ctx; } ;
struct ahc_softc {int /*<<< orphan*/  our_id; } ;
struct ahc_linux_device {size_t active; int openings; size_t tags_on_last_queuefull; size_t maxtags; int flags; int /*<<< orphan*/  last_queuefull_same_count; int /*<<< orphan*/  tag_success_count; } ;
struct ahc_devinfo {int dummy; } ;
struct TYPE_2__ {scalar_t__ channel; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int AHC_DEV_Q_BASIC ; 
 int /*<<< orphan*/  AHC_LOCK_TAGS_COUNT ; 
 int /*<<< orphan*/  AHC_QUEUE_BASIC ; 
 int /*<<< orphan*/  AHC_QUEUE_TAGGED ; 
 int AHC_SHOW_SENSE ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int DRIVER_SENSE ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int SCB_SENSE ; 
 size_t SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  SCSI_STATUS_BUSY ; 
#define  SCSI_STATUS_CHECK_COND 130 
#define  SCSI_STATUS_CMD_TERMINATED 129 
 int /*<<< orphan*/  SCSI_STATUS_OK ; 
#define  SCSI_STATUS_QUEUE_FULL 128 
 int /*<<< orphan*/  ahc_compile_devinfo (struct ahc_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int ahc_debug ; 
 int ahc_get_scsi_status (struct scb*) ; 
 int /*<<< orphan*/  ahc_get_sense_buf (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahc_get_sense_residual (struct scb*) ; 
 int /*<<< orphan*/  ahc_platform_set_tags (struct ahc_softc*,struct scsi_device*,struct ahc_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_print_path (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahc_set_scsi_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,size_t) ; 
 size_t min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct ahc_linux_device* scsi_transport_device_data (struct scsi_device*) ; 

__attribute__((used)) static void
ahc_linux_handle_scsi_status(struct ahc_softc *ahc,
			     struct scsi_device *sdev, struct scb *scb)
{
	struct	ahc_devinfo devinfo;
	struct ahc_linux_device *dev = scsi_transport_device_data(sdev);

	ahc_compile_devinfo(&devinfo,
			    ahc->our_id,
			    sdev->sdev_target->id, sdev->lun,
			    sdev->sdev_target->channel == 0 ? 'A' : 'B',
			    ROLE_INITIATOR);
	
	/*
	 * We don't currently trust the mid-layer to
	 * properly deal with queue full or busy.  So,
	 * when one occurs, we tell the mid-layer to
	 * unconditionally requeue the command to us
	 * so that we can retry it ourselves.  We also
	 * implement our own throttling mechanism so
	 * we don't clobber the device with too many
	 * commands.
	 */
	switch (ahc_get_scsi_status(scb)) {
	default:
		break;
	case SCSI_STATUS_CHECK_COND:
	case SCSI_STATUS_CMD_TERMINATED:
	{
		struct scsi_cmnd *cmd;

		/*
		 * Copy sense information to the OS's cmd
		 * structure if it is available.
		 */
		cmd = scb->io_ctx;
		if (scb->flags & SCB_SENSE) {
			u_int sense_size;

			sense_size = min(sizeof(struct scsi_sense_data)
				       - ahc_get_sense_residual(scb),
					 (u_long)SCSI_SENSE_BUFFERSIZE);
			memcpy(cmd->sense_buffer,
			       ahc_get_sense_buf(ahc, scb), sense_size);
			if (sense_size < SCSI_SENSE_BUFFERSIZE)
				memset(&cmd->sense_buffer[sense_size], 0,
				       SCSI_SENSE_BUFFERSIZE - sense_size);
			cmd->result |= (DRIVER_SENSE << 24);
#ifdef AHC_DEBUG
			if (ahc_debug & AHC_SHOW_SENSE) {
				int i;

				printf("Copied %d bytes of sense data:",
				       sense_size);
				for (i = 0; i < sense_size; i++) {
					if ((i & 0xF) == 0)
						printf("\n");
					printf("0x%x ", cmd->sense_buffer[i]);
				}
				printf("\n");
			}
#endif
		}
		break;
	}
	case SCSI_STATUS_QUEUE_FULL:
	{
		/*
		 * By the time the core driver has returned this
		 * command, all other commands that were queued
		 * to us but not the device have been returned.
		 * This ensures that dev->active is equal to
		 * the number of commands actually queued to
		 * the device.
		 */
		dev->tag_success_count = 0;
		if (dev->active != 0) {
			/*
			 * Drop our opening count to the number
			 * of commands currently outstanding.
			 */
			dev->openings = 0;
/*
			ahc_print_path(ahc, scb);
			printf("Dropping tag count to %d\n", dev->active);
 */
			if (dev->active == dev->tags_on_last_queuefull) {

				dev->last_queuefull_same_count++;
				/*
				 * If we repeatedly see a queue full
				 * at the same queue depth, this
				 * device has a fixed number of tag
				 * slots.  Lock in this tag depth
				 * so we stop seeing queue fulls from
				 * this device.
				 */
				if (dev->last_queuefull_same_count
				 == AHC_LOCK_TAGS_COUNT) {
					dev->maxtags = dev->active;
					ahc_print_path(ahc, scb);
					printf("Locking max tag count at %d\n",
					       dev->active);
				}
			} else {
				dev->tags_on_last_queuefull = dev->active;
				dev->last_queuefull_same_count = 0;
			}
			ahc_set_transaction_status(scb, CAM_REQUEUE_REQ);
			ahc_set_scsi_status(scb, SCSI_STATUS_OK);
			ahc_platform_set_tags(ahc, sdev, &devinfo,
				     (dev->flags & AHC_DEV_Q_BASIC)
				   ? AHC_QUEUE_BASIC : AHC_QUEUE_TAGGED);
			break;
		}
		/*
		 * Drop down to a single opening, and treat this
		 * as if the target returned BUSY SCSI status.
		 */
		dev->openings = 1;
		ahc_set_scsi_status(scb, SCSI_STATUS_BUSY);
		ahc_platform_set_tags(ahc, sdev, &devinfo,
			     (dev->flags & AHC_DEV_Q_BASIC)
			   ? AHC_QUEUE_BASIC : AHC_QUEUE_TAGGED);
		break;
	}
	}
}