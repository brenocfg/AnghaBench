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
struct usb_ov511 {int packet_size; int maxwidth; int maxheight; size_t curframe; int minwidth; int minheight; struct ov511_frame* frame; TYPE_1__* dev; } ;
struct timeval {int dummy; } ;
struct ov511_frame {int rawwidth; int rawheight; int bytes_recvd; scalar_t__ scanstate; scalar_t__ grabstate; int snapshot; unsigned char compressed; scalar_t__ rawdata; int /*<<< orphan*/  wq; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  in ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ FRAME_DONE ; 
 scalar_t__ FRAME_GRABBING ; 
 scalar_t__ FRAME_READY ; 
 scalar_t__ MAX_FRAME_SIZE (int,int) ; 
 int MAX_RAW_DATA_SIZE (int,int) ; 
 int OV511_NUMFRAMES ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (int,int,int) ; 
 scalar_t__ STATE_LINES ; 
 scalar_t__ STATE_SCANNING ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int dumppix ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,int) ; 
 scalar_t__ printph ; 
 int /*<<< orphan*/  remove_zeros ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ov511_move_data(struct usb_ov511 *ov, unsigned char *in, int n)
{
	int num, offset;
	int pnum = in[ov->packet_size - 1];		/* Get packet number */
	int max_raw = MAX_RAW_DATA_SIZE(ov->maxwidth, ov->maxheight);
	struct ov511_frame *frame = &ov->frame[ov->curframe];
	struct timeval *ts;

	/* SOF/EOF packets have 1st to 8th bytes zeroed and the 9th
	 * byte non-zero. The EOF packet has image width/height in the
	 * 10th and 11th bytes. The 9th byte is given as follows:
	 *
	 * bit 7: EOF
	 *     6: compression enabled
	 *     5: 422/420/400 modes
	 *     4: 422/420/400 modes
	 *     3: 1
	 *     2: snapshot button on
	 *     1: snapshot frame
	 *     0: even/odd field
	 */

	if (printph) {
		dev_info(&ov->dev->dev,
			 "ph(%3d): %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x\n",
			 pnum, in[0], in[1], in[2], in[3], in[4], in[5], in[6],
			 in[7], in[8], in[9], in[10], in[11]);
	}

	/* Check for SOF/EOF packet */
	if ((in[0] | in[1] | in[2] | in[3] | in[4] | in[5] | in[6] | in[7]) ||
	    (~in[8] & 0x08))
		goto check_middle;

	/* Frame end */
	if (in[8] & 0x80) {
		ts = (struct timeval *)(frame->data
		      + MAX_FRAME_SIZE(ov->maxwidth, ov->maxheight));
		do_gettimeofday(ts);

		/* Get the actual frame size from the EOF header */
		frame->rawwidth = ((int)(in[9]) + 1) * 8;
		frame->rawheight = ((int)(in[10]) + 1) * 8;

		PDEBUG(4, "Frame end, frame=%d, pnum=%d, w=%d, h=%d, recvd=%d",
			ov->curframe, pnum, frame->rawwidth, frame->rawheight,
			frame->bytes_recvd);

		/* Validate the header data */
		RESTRICT_TO_RANGE(frame->rawwidth, ov->minwidth, ov->maxwidth);
		RESTRICT_TO_RANGE(frame->rawheight, ov->minheight,
				  ov->maxheight);

		/* Don't allow byte count to exceed buffer size */
		RESTRICT_TO_RANGE(frame->bytes_recvd, 8, max_raw);

		if (frame->scanstate == STATE_LINES) {
			int nextf;

			frame->grabstate = FRAME_DONE;
			wake_up_interruptible(&frame->wq);

			/* If next frame is ready or grabbing,
			 * point to it */
			nextf = (ov->curframe + 1) % OV511_NUMFRAMES;
			if (ov->frame[nextf].grabstate == FRAME_READY
			    || ov->frame[nextf].grabstate == FRAME_GRABBING) {
				ov->curframe = nextf;
				ov->frame[nextf].scanstate = STATE_SCANNING;
			} else {
				if (frame->grabstate == FRAME_DONE) {
					PDEBUG(4, "** Frame done **");
				} else {
					PDEBUG(4, "Frame not ready? state = %d",
						ov->frame[nextf].grabstate);
				}

				ov->curframe = -1;
			}
		} else {
			PDEBUG(5, "Frame done, but not scanning");
		}
		/* Image corruption caused by misplaced frame->segment = 0
		 * fixed by carlosf@conectiva.com.br
		 */
	} else {
		/* Frame start */
		PDEBUG(4, "Frame start, framenum = %d", ov->curframe);

		/* Check to see if it's a snapshot frame */
		/* FIXME?? Should the snapshot reset go here? Performance? */
		if (in[8] & 0x02) {
			frame->snapshot = 1;
			PDEBUG(3, "snapshot detected");
		}

		frame->scanstate = STATE_LINES;
		frame->bytes_recvd = 0;
		frame->compressed = in[8] & 0x40;
	}

check_middle:
	/* Are we in a frame? */
	if (frame->scanstate != STATE_LINES) {
		PDEBUG(5, "Not in a frame; packet skipped");
		return;
	}

	/* If frame start, skip header */
	if (frame->bytes_recvd == 0)
		offset = 9;
	else
		offset = 0;

	num = n - offset - 1;

	/* Dump all data exactly as received */
	if (dumppix == 2) {
		frame->bytes_recvd += n - 1;
		if (frame->bytes_recvd <= max_raw)
			memcpy(frame->rawdata + frame->bytes_recvd - (n - 1),
				in, n - 1);
		else
			PDEBUG(3, "Raw data buffer overrun!! (%d)",
				frame->bytes_recvd - max_raw);
	} else if (!frame->compressed && !remove_zeros) {
		frame->bytes_recvd += num;
		if (frame->bytes_recvd <= max_raw)
			memcpy(frame->rawdata + frame->bytes_recvd - num,
				in + offset, num);
		else
			PDEBUG(3, "Raw data buffer overrun!! (%d)",
				frame->bytes_recvd - max_raw);
	} else { /* Remove all-zero FIFO lines (aligned 32-byte blocks) */
		int b, read = 0, allzero, copied = 0;
		if (offset) {
			frame->bytes_recvd += 32 - offset;	// Bytes out
			memcpy(frame->rawdata,	in + offset, 32 - offset);
			read += 32;
		}

		while (read < n - 1) {
			allzero = 1;
			for (b = 0; b < 32; b++) {
				if (in[read + b]) {
					allzero = 0;
					break;
				}
			}

			if (allzero) {
				/* Don't copy it */
			} else {
				if (frame->bytes_recvd + copied + 32 <= max_raw)
				{
					memcpy(frame->rawdata
						+ frame->bytes_recvd + copied,
						in + read, 32);
					copied += 32;
				} else {
					PDEBUG(3, "Raw data buffer overrun!!");
				}
			}
			read += 32;
		}

		frame->bytes_recvd += copied;
	}
}