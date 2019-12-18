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
struct pwc_frame_buf {int filled; scalar_t__ data; } ;
struct pwc_device {int type; scalar_t__ drop_frames; unsigned char vmirror; int frame_total_size; int /*<<< orphan*/  vframe_count; int /*<<< orphan*/  vframes_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWC_DEBUG_FLOW (char*,int) ; 
 int /*<<< orphan*/  PWC_TRACE (char*) ; 
 int /*<<< orphan*/  pwc_frame_dumped (struct pwc_device*) ; 
 scalar_t__ pwc_next_fill_frame (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_snapshot_button (struct pwc_device*,unsigned char) ; 

__attribute__((used)) static int pwc_rcv_short_packet(struct pwc_device *pdev, const struct pwc_frame_buf *fbuf)
{
	int awake = 0;

	/* The ToUCam Fun CMOS sensor causes the firmware to send 2 or 3 bogus
	   frames on the USB wire after an exposure change. This conditition is
	   however detected  in the cam and a bit is set in the header.
	   */
	if (pdev->type == 730) {
		unsigned char *ptr = (unsigned char *)fbuf->data;

		if (ptr[1] == 1 && ptr[0] & 0x10) {
			PWC_TRACE("Hyundai CMOS sensor bug. Dropping frame.\n");
			pdev->drop_frames += 2;
			pdev->vframes_error++;
		}
		if ((ptr[0] ^ pdev->vmirror) & 0x01) {
			pwc_snapshot_button(pdev, ptr[0] & 0x01);
		}
		if ((ptr[0] ^ pdev->vmirror) & 0x02) {
			if (ptr[0] & 0x02)
				PWC_TRACE("Image is mirrored.\n");
			else
				PWC_TRACE("Image is normal.\n");
		}
		pdev->vmirror = ptr[0] & 0x03;
		/* Sometimes the trailer of the 730 is still sent as a 4 byte packet
		   after a short frame; this condition is filtered out specifically. A 4 byte
		   frame doesn't make sense anyway.
		   So we get either this sequence:
		   drop_bit set -> 4 byte frame -> short frame -> good frame
		   Or this one:
		   drop_bit set -> short frame -> good frame
		   So we drop either 3 or 2 frames in all!
		   */
		if (fbuf->filled == 4)
			pdev->drop_frames++;
	}
	else if (pdev->type == 740 || pdev->type == 720) {
		unsigned char *ptr = (unsigned char *)fbuf->data;
		if ((ptr[0] ^ pdev->vmirror) & 0x01) {
			pwc_snapshot_button(pdev, ptr[0] & 0x01);
		}
		pdev->vmirror = ptr[0] & 0x03;
	}

	/* In case we were instructed to drop the frame, do so silently.
	   The buffer pointers are not updated either (but the counters are reset below).
	   */
	if (pdev->drop_frames > 0)
		pdev->drop_frames--;
	else {
		/* Check for underflow first */
		if (fbuf->filled < pdev->frame_total_size) {
			PWC_DEBUG_FLOW("Frame buffer underflow (%d bytes);"
				       " discarded.\n", fbuf->filled);
			pdev->vframes_error++;
		}
		else {
			/* Send only once per EOF */
			awake = 1; /* delay wake_ups */

			/* Find our next frame to fill. This will always succeed, since we
			 * nick a frame from either empty or full list, but if we had to
			 * take it from the full list, it means a frame got dropped.
			 */
			if (pwc_next_fill_frame(pdev))
				pwc_frame_dumped(pdev);

		}
	} /* !drop_frames */
	pdev->vframe_count++;
	return awake;
}