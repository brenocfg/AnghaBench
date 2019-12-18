#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct us_data {int fflags; scalar_t__ max_lun; int /*<<< orphan*/  dev_mutex; TYPE_2__* srb; int /*<<< orphan*/  dflags; int /*<<< orphan*/  notify; int /*<<< orphan*/  (* proto_handler ) (TYPE_2__*,struct us_data*) ;int /*<<< orphan*/  cmnd_ready; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_6__ {int result; scalar_t__ sc_data_direction; scalar_t__* cmnd; int /*<<< orphan*/  (* scsi_done ) (TYPE_2__*) ;TYPE_1__* device; } ;
struct TYPE_5__ {scalar_t__ lun; scalar_t__ id; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
 scalar_t__ DMA_BIDIRECTIONAL ; 
 scalar_t__ INQUIRY ; 
 int SAM_STAT_GOOD ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  US_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int /*<<< orphan*/  US_FLIDX_ABORTING ; 
 int /*<<< orphan*/  US_FLIDX_TIMED_OUT ; 
 int US_FL_FIX_INQUIRY ; 
 int US_FL_SCM_MULT_TARG ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_inquiry_response (struct us_data*,unsigned char*,int) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  scsi_lock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_unlock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct us_data*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* us_to_host (struct us_data*) ; 
 int /*<<< orphan*/  usb_stor_show_command (TYPE_2__*) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usb_stor_control_thread(void * __us)
{
	struct us_data *us = (struct us_data *)__us;
	struct Scsi_Host *host = us_to_host(us);

	for(;;) {
		US_DEBUGP("*** thread sleeping.\n");
		if (wait_for_completion_interruptible(&us->cmnd_ready))
			break;

		US_DEBUGP("*** thread awakened.\n");

		/* lock the device pointers */
		mutex_lock(&(us->dev_mutex));

		/* lock access to the state */
		scsi_lock(host);

		/* When we are called with no command pending, we're done */
		if (us->srb == NULL) {
			scsi_unlock(host);
			mutex_unlock(&us->dev_mutex);
			US_DEBUGP("-- exiting\n");
			break;
		}

		/* has the command timed out *already* ? */
		if (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) {
			us->srb->result = DID_ABORT << 16;
			goto SkipForAbort;
		}

		scsi_unlock(host);

		/* reject the command if the direction indicator 
		 * is UNKNOWN
		 */
		if (us->srb->sc_data_direction == DMA_BIDIRECTIONAL) {
			US_DEBUGP("UNKNOWN data direction\n");
			us->srb->result = DID_ERROR << 16;
		}

		/* reject if target != 0 or if LUN is higher than
		 * the maximum known LUN
		 */
		else if (us->srb->device->id && 
				!(us->fflags & US_FL_SCM_MULT_TARG)) {
			US_DEBUGP("Bad target number (%d:%d)\n",
				  us->srb->device->id, us->srb->device->lun);
			us->srb->result = DID_BAD_TARGET << 16;
		}

		else if (us->srb->device->lun > us->max_lun) {
			US_DEBUGP("Bad LUN (%d:%d)\n",
				  us->srb->device->id, us->srb->device->lun);
			us->srb->result = DID_BAD_TARGET << 16;
		}

		/* Handle those devices which need us to fake 
		 * their inquiry data */
		else if ((us->srb->cmnd[0] == INQUIRY) &&
			    (us->fflags & US_FL_FIX_INQUIRY)) {
			unsigned char data_ptr[36] = {
			    0x00, 0x80, 0x02, 0x02,
			    0x1F, 0x00, 0x00, 0x00};

			US_DEBUGP("Faking INQUIRY command\n");
			fill_inquiry_response(us, data_ptr, 36);
			us->srb->result = SAM_STAT_GOOD;
		}

		/* we've got a command, let's do it! */
		else {
			US_DEBUG(usb_stor_show_command(us->srb));
			us->proto_handler(us->srb, us);
		}

		/* lock access to the state */
		scsi_lock(host);

		/* indicate that the command is done */
		if (us->srb->result != DID_ABORT << 16) {
			US_DEBUGP("scsi cmd done, result=0x%x\n", 
				   us->srb->result);
			us->srb->scsi_done(us->srb);
		} else {
SkipForAbort:
			US_DEBUGP("scsi command aborted\n");
		}

		/* If an abort request was received we need to signal that
		 * the abort has finished.  The proper test for this is
		 * the TIMED_OUT flag, not srb->result == DID_ABORT, because
		 * the timeout might have occurred after the command had
		 * already completed with a different result code. */
		if (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) {
			complete(&(us->notify));

			/* Allow USB transfers to resume */
			clear_bit(US_FLIDX_ABORTING, &us->dflags);
			clear_bit(US_FLIDX_TIMED_OUT, &us->dflags);
		}

		/* finished working on this command */
		us->srb = NULL;
		scsi_unlock(host);

		/* unlock the device pointers */
		mutex_unlock(&us->dev_mutex);
	} /* for (;;) */

	/* Wait until we are told to stop */
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (kthread_should_stop())
			break;
		schedule();
	}
	__set_current_state(TASK_RUNNING);
	return 0;
}