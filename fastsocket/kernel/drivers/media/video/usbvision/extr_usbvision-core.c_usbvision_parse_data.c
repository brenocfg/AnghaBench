#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usbvision_frame {scalar_t__ scanstate; long scanlength; int /*<<< orphan*/  grabstate; int /*<<< orphan*/  frame; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timestamp; } ;
struct usb_usbvision {scalar_t__ isoc_mode; int /*<<< orphan*/  wait_frame; int /*<<< orphan*/  frame_num; int /*<<< orphan*/  queue_lock; struct usbvision_frame* cur_frame; int /*<<< orphan*/  outqueue; } ;
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PARSE ; 
 scalar_t__ ISOC_MODE_COMPRESS ; 
 scalar_t__ ISOC_MODE_YUV420 ; 
 scalar_t__ ISOC_MODE_YUV422 ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_state_done ; 
 int /*<<< orphan*/  frame_state_grabbing ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_state_continue ; 
 int parse_state_next_frame ; 
 int parse_state_out ; 
 scalar_t__ scan_state_lines ; 
 scalar_t__ scan_state_scanning ; 
 scalar_t__ scratch_len (struct usb_usbvision*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usbvision_find_header (struct usb_usbvision*) ; 
 int usbvision_parse_compress (struct usb_usbvision*,long*) ; 
 int usbvision_parse_lines_420 (struct usb_usbvision*,long*) ; 
 int usbvision_parse_lines_422 (struct usb_usbvision*,long*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbvision_parse_data(struct usb_usbvision *usbvision)
{
	struct usbvision_frame *frame;
	enum parse_state newstate;
	long copylen = 0;
	unsigned long lock_flags;

	frame = usbvision->cur_frame;

	PDEBUG(DBG_PARSE, "parsing len=%d\n", scratch_len(usbvision));

	while (1) {
		newstate = parse_state_out;
		if (scratch_len(usbvision)) {
			if (frame->scanstate == scan_state_scanning) {
				newstate = usbvision_find_header(usbvision);
			} else if (frame->scanstate == scan_state_lines) {
				if (usbvision->isoc_mode == ISOC_MODE_YUV420)
					newstate = usbvision_parse_lines_420(usbvision, &copylen);
				else if (usbvision->isoc_mode == ISOC_MODE_YUV422)
					newstate = usbvision_parse_lines_422(usbvision, &copylen);
				else if (usbvision->isoc_mode == ISOC_MODE_COMPRESS)
					newstate = usbvision_parse_compress(usbvision, &copylen);
			}
		}
		if (newstate == parse_state_continue)
			continue;
		if ((newstate == parse_state_next_frame) || (newstate == parse_state_out))
			break;
		return;	/* parse_state_end_parse */
	}

	if (newstate == parse_state_next_frame) {
		frame->grabstate = frame_state_done;
		do_gettimeofday(&(frame->timestamp));
		frame->sequence = usbvision->frame_num;

		spin_lock_irqsave(&usbvision->queue_lock, lock_flags);
		list_move_tail(&(frame->frame), &usbvision->outqueue);
		usbvision->cur_frame = NULL;
		spin_unlock_irqrestore(&usbvision->queue_lock, lock_flags);

		usbvision->frame_num++;

		/* This will cause the process to request another frame. */
		if (waitqueue_active(&usbvision->wait_frame)) {
			PDEBUG(DBG_PARSE, "Wake up !");
			wake_up_interruptible(&usbvision->wait_frame);
		}
	} else {
		frame->grabstate = frame_state_grabbing;
	}

	/* Update the frame's uncompressed length. */
	frame->scanlength += copylen;
}