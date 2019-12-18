#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fsg_dev {int data_dir; int /*<<< orphan*/  bulk_out; int /*<<< orphan*/  short_packet_received; int /*<<< orphan*/  residue; struct fsg_buffhd* next_buffhd_to_fill; int /*<<< orphan*/  bulk_in; TYPE_1__* curlun; int /*<<< orphan*/  data_size; } ;
struct fsg_buffhd {struct fsg_buffhd* next; int /*<<< orphan*/  state; int /*<<< orphan*/  inreq_busy; TYPE_2__* inreq; } ;
struct TYPE_6__ {int /*<<< orphan*/  can_stall; } ;
struct TYPE_5__ {int zero; } ;
struct TYPE_4__ {int /*<<< orphan*/  sense_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_STATE_EMPTY ; 
#define  DATA_DIR_FROM_HOST 131 
#define  DATA_DIR_NONE 130 
#define  DATA_DIR_TO_HOST 129 
#define  DATA_DIR_UNKNOWN 128 
 int EINTR ; 
 int /*<<< orphan*/  FSG_STATE_ABORT_BULK_OUT ; 
 int /*<<< orphan*/  SS_NO_SENSE ; 
 int /*<<< orphan*/  fsg_set_halt (struct fsg_dev*,int /*<<< orphan*/ ) ; 
 int halt_bulk_in_endpoint (struct fsg_dev*) ; 
 TYPE_3__ mod_data ; 
 int pad_with_zeros (struct fsg_dev*) ; 
 int /*<<< orphan*/  raise_exception (struct fsg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_transfer (struct fsg_dev*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int throw_away_data (struct fsg_dev*) ; 
 int /*<<< orphan*/  transport_is_bbb () ; 

__attribute__((used)) static int finish_reply(struct fsg_dev *fsg)
{
	struct fsg_buffhd	*bh = fsg->next_buffhd_to_fill;
	int			rc = 0;

	switch (fsg->data_dir) {
	case DATA_DIR_NONE:
		break;			// Nothing to send

	/* If we don't know whether the host wants to read or write,
	 * this must be CB or CBI with an unknown command.  We mustn't
	 * try to send or receive any data.  So stall both bulk pipes
	 * if we can and wait for a reset. */
	case DATA_DIR_UNKNOWN:
		if (mod_data.can_stall) {
			fsg_set_halt(fsg, fsg->bulk_out);
			rc = halt_bulk_in_endpoint(fsg);
		}
		break;

	/* All but the last buffer of data must have already been sent */
	case DATA_DIR_TO_HOST:
		if (fsg->data_size == 0)
			;		// Nothing to send

		/* If there's no residue, simply send the last buffer */
		else if (fsg->residue == 0) {
			bh->inreq->zero = 0;
			start_transfer(fsg, fsg->bulk_in, bh->inreq,
					&bh->inreq_busy, &bh->state);
			fsg->next_buffhd_to_fill = bh->next;
		}

		/* There is a residue.  For CB and CBI, simply mark the end
		 * of the data with a short packet.  However, if we are
		 * allowed to stall, there was no data at all (residue ==
		 * data_size), and the command failed (invalid LUN or
		 * sense data is set), then halt the bulk-in endpoint
		 * instead. */
		else if (!transport_is_bbb()) {
			if (mod_data.can_stall &&
					fsg->residue == fsg->data_size &&
	(!fsg->curlun || fsg->curlun->sense_data != SS_NO_SENSE)) {
				bh->state = BUF_STATE_EMPTY;
				rc = halt_bulk_in_endpoint(fsg);
			} else {
				bh->inreq->zero = 1;
				start_transfer(fsg, fsg->bulk_in, bh->inreq,
						&bh->inreq_busy, &bh->state);
				fsg->next_buffhd_to_fill = bh->next;
			}
		}

		/* For Bulk-only, if we're allowed to stall then send the
		 * short packet and halt the bulk-in endpoint.  If we can't
		 * stall, pad out the remaining data with 0's. */
		else {
			if (mod_data.can_stall) {
				bh->inreq->zero = 1;
				start_transfer(fsg, fsg->bulk_in, bh->inreq,
						&bh->inreq_busy, &bh->state);
				fsg->next_buffhd_to_fill = bh->next;
				rc = halt_bulk_in_endpoint(fsg);
			} else
				rc = pad_with_zeros(fsg);
		}
		break;

	/* We have processed all we want from the data the host has sent.
	 * There may still be outstanding bulk-out requests. */
	case DATA_DIR_FROM_HOST:
		if (fsg->residue == 0)
			;		// Nothing to receive

		/* Did the host stop sending unexpectedly early? */
		else if (fsg->short_packet_received) {
			raise_exception(fsg, FSG_STATE_ABORT_BULK_OUT);
			rc = -EINTR;
		}

		/* We haven't processed all the incoming data.  Even though
		 * we may be allowed to stall, doing so would cause a race.
		 * The controller may already have ACK'ed all the remaining
		 * bulk-out packets, in which case the host wouldn't see a
		 * STALL.  Not realizing the endpoint was halted, it wouldn't
		 * clear the halt -- leading to problems later on. */
#if 0
		else if (mod_data.can_stall) {
			fsg_set_halt(fsg, fsg->bulk_out);
			raise_exception(fsg, FSG_STATE_ABORT_BULK_OUT);
			rc = -EINTR;
		}
#endif

		/* We can't stall.  Read in the excess data and throw it
		 * all away. */
		else
			rc = throw_away_data(fsg);
		break;
	}
	return rc;
}