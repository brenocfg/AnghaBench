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
struct video_data {int /*<<< orphan*/  bubble_work; int /*<<< orphan*/  is_streaming; } ;
struct urb {int number_of_packets; scalar_t__ transfer_buffer; struct front_face* context; } ;
struct front_face {TYPE_1__* pd; } ;
struct TYPE_2__ {struct video_data video_data; } ;

/* Variables and functions */
#define  GET_NONE 131 
#define  GET_SUCCESS 130 
#define  GET_TOO_MUCH_BUBBLE 129 
#define  GET_TRAILER 128 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ISO_PKT_SIZE ; 
 int /*<<< orphan*/  check_trailer (struct video_data*,char*,int) ; 
 int /*<<< orphan*/  copy_vbi_video_data (struct video_data*,char*,int) ; 
 int get_chunk (int,struct urb*,int*,int*,int*) ; 
 int /*<<< orphan*/  get_video_frame (struct front_face*,struct video_data*) ; 
 int /*<<< orphan*/  log (char*,...) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void urb_complete_iso(struct urb *urb)
{
	struct front_face *front = urb->context;
	struct video_data *video = &front->pd->video_data;
	int bubble_err = 0, head = 0, tail = 0;
	char *src = (char *)urb->transfer_buffer;
	int ret = 0;

	if (!video->is_streaming)
		return;

	do {
		if (!get_video_frame(front, video))
			goto out;

		switch (get_chunk(head, urb, &head, &tail, &bubble_err)) {
		case GET_SUCCESS:
			copy_vbi_video_data(video, src + (head * ISO_PKT_SIZE),
					(tail - head + 1) * ISO_PKT_SIZE);
			break;
		case GET_TRAILER:
			check_trailer(video, src + (head * ISO_PKT_SIZE),
					ISO_PKT_SIZE);
			break;
		case GET_NONE:
			goto out;
		case GET_TOO_MUCH_BUBBLE:
			log("\t We got too much bubble");
			schedule_work(&video->bubble_work);
			return;
		}
	} while (head = tail + 1, head < urb->number_of_packets);

out:
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	if (ret)
		log("usb_submit_urb err : %d", ret);
}