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
struct usb_ov511 {int curframe; long maxwidth; long maxheight; struct ov511_frame* frame; int /*<<< orphan*/  dev; } ;
struct ov511_frame {scalar_t__ grabstate; long width; long height; scalar_t__ snapshot; int /*<<< orphan*/  scanstate; } ;

/* Variables and functions */
 scalar_t__ FRAME_GRABBING ; 
 scalar_t__ FRAME_READY ; 
 int OV511_NUMFRAMES ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int,long,...) ; 
 int /*<<< orphan*/  STATE_SCANNING ; 

__attribute__((used)) static int
ov51x_new_frame(struct usb_ov511 *ov, int framenum)
{
	struct ov511_frame *frame;
	int newnum;

	PDEBUG(4, "ov->curframe = %d, framenum = %d", ov->curframe, framenum);

	if (!ov->dev)
		return -1;

	/* If we're not grabbing a frame right now and the other frame is */
	/* ready to be grabbed into, then use it instead */
	if (ov->curframe == -1) {
		newnum = (framenum - 1 + OV511_NUMFRAMES) % OV511_NUMFRAMES;
		if (ov->frame[newnum].grabstate == FRAME_READY)
			framenum = newnum;
	} else
		return 0;

	frame = &ov->frame[framenum];

	PDEBUG(4, "framenum = %d, width = %d, height = %d", framenum,
	       frame->width, frame->height);

	frame->grabstate = FRAME_GRABBING;
	frame->scanstate = STATE_SCANNING;
	frame->snapshot = 0;

	ov->curframe = framenum;

	/* Make sure it's not too big */
	if (frame->width > ov->maxwidth)
		frame->width = ov->maxwidth;

	frame->width &= ~7L;		/* Multiple of 8 */

	if (frame->height > ov->maxheight)
		frame->height = ov->maxheight;

	frame->height &= ~3L;		/* Multiple of 4 */

	return 0;
}