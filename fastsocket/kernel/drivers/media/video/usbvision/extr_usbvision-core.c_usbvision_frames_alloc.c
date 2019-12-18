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
struct TYPE_3__ {int bytes_per_pixel; } ;
struct usb_usbvision {int max_frame_size; int curwidth; int curheight; int num_frames; int fbuf_size; int stretch_width; int stretch_height; TYPE_2__* frame; scalar_t__ fbuf; int /*<<< orphan*/  wait_stream; int /*<<< orphan*/  wait_frame; int /*<<< orphan*/  queue_lock; TYPE_1__ palette; } ;
struct TYPE_4__ {int index; int width; int height; scalar_t__ bytes_read; scalar_t__ data; int /*<<< orphan*/  grabstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  frame_state_unused ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ usbvision_rvmalloc (int) ; 

int usbvision_frames_alloc(struct usb_usbvision *usbvision, int number_of_frames)
{
	int i;

	/* needs to be page aligned cause the buffers can be mapped individually! */
	usbvision->max_frame_size = PAGE_ALIGN(usbvision->curwidth *
						usbvision->curheight *
						usbvision->palette.bytes_per_pixel);

	/* Try to do my best to allocate the frames the user want in the remaining memory */
	usbvision->num_frames = number_of_frames;
	while (usbvision->num_frames > 0) {
		usbvision->fbuf_size = usbvision->num_frames * usbvision->max_frame_size;
		usbvision->fbuf = usbvision_rvmalloc(usbvision->fbuf_size);
		if (usbvision->fbuf)
			break;
		usbvision->num_frames--;
	}

	spin_lock_init(&usbvision->queue_lock);
	init_waitqueue_head(&usbvision->wait_frame);
	init_waitqueue_head(&usbvision->wait_stream);

	/* Allocate all buffers */
	for (i = 0; i < usbvision->num_frames; i++) {
		usbvision->frame[i].index = i;
		usbvision->frame[i].grabstate = frame_state_unused;
		usbvision->frame[i].data = usbvision->fbuf +
			i * usbvision->max_frame_size;
		/*
		 * Set default sizes for read operation.
		 */
		usbvision->stretch_width = 1;
		usbvision->stretch_height = 1;
		usbvision->frame[i].width = usbvision->curwidth;
		usbvision->frame[i].height = usbvision->curheight;
		usbvision->frame[i].bytes_read = 0;
	}
	PDEBUG(DBG_FUNC, "allocated %d frames (%d bytes per frame)",
			usbvision->num_frames, usbvision->max_frame_size);
	return usbvision->num_frames;
}