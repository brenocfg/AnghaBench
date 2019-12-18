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
struct video_data {int /*<<< orphan*/  is_streaming; } ;
struct urb {int actual_length; int transfer_buffer_length; scalar_t__ status; scalar_t__ transfer_buffer; struct front_face* context; } ;
struct front_face {TYPE_1__* pd; } ;
struct TYPE_2__ {struct video_data video_data; } ;

/* Variables and functions */
 scalar_t__ EPROTO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  check_trailer (struct video_data*,char*,int) ; 
 int /*<<< orphan*/  copy_vbi_video_data (struct video_data*,char*,int) ; 
 int /*<<< orphan*/  get_video_frame (struct front_face*,struct video_data*) ; 
 int /*<<< orphan*/  log (char*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void urb_complete_bulk(struct urb *urb)
{
	struct front_face *front = urb->context;
	struct video_data *video = &front->pd->video_data;
	char *src = (char *)urb->transfer_buffer;
	int count = urb->actual_length;
	int ret = 0;

	if (!video->is_streaming || urb->status) {
		if (urb->status == -EPROTO)
			goto resend_it;
		return;
	}
	if (!get_video_frame(front, video))
		goto resend_it;

	if (count == urb->transfer_buffer_length)
		copy_vbi_video_data(video, src, count);
	else
		check_trailer(video, src, count);

resend_it:
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	if (ret)
		log(" submit failed: error %d", ret);
}