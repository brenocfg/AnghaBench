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
struct synthvid_pointer_shape {int dummy; } ;
struct synthvid_pointer_position {int dummy; } ;
struct synthvid_msg_hdr {int dummy; } ;
struct TYPE_6__ {int is_argb; int width; int height; int* data; scalar_t__ hot_y; scalar_t__ hot_x; int /*<<< orphan*/  part_idx; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int is_visible; scalar_t__ image_y; scalar_t__ image_x; scalar_t__ video_output; } ;
struct synthvid_msg {TYPE_3__ ptr_shape; TYPE_2__ vid_hdr; TYPE_1__ ptr_pos; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_COMPLETE ; 
 int /*<<< orphan*/  SYNTHVID_POINTER_POSITION ; 
 int /*<<< orphan*/  SYNTHVID_POINTER_SHAPE ; 
 int /*<<< orphan*/  memset (struct synthvid_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synthvid_send (struct hv_device*,struct synthvid_msg*) ; 

__attribute__((used)) static int synthvid_send_ptr(struct hv_device *hdev)
{
	struct synthvid_msg msg;

	memset(&msg, 0, sizeof(struct synthvid_msg));
	msg.vid_hdr.type = SYNTHVID_POINTER_POSITION;
	msg.vid_hdr.size = sizeof(struct synthvid_msg_hdr) +
		sizeof(struct synthvid_pointer_position);
	msg.ptr_pos.is_visible = 1;
	msg.ptr_pos.video_output = 0;
	msg.ptr_pos.image_x = 0;
	msg.ptr_pos.image_y = 0;
	synthvid_send(hdev, &msg);

	memset(&msg, 0, sizeof(struct synthvid_msg));
	msg.vid_hdr.type = SYNTHVID_POINTER_SHAPE;
	msg.vid_hdr.size = sizeof(struct synthvid_msg_hdr) +
		sizeof(struct synthvid_pointer_shape);
	msg.ptr_shape.part_idx = CURSOR_COMPLETE;
	msg.ptr_shape.is_argb = 1;
	msg.ptr_shape.width = 1;
	msg.ptr_shape.height = 1;
	msg.ptr_shape.hot_x = 0;
	msg.ptr_shape.hot_y = 0;
	msg.ptr_shape.data[0] = 0;
	msg.ptr_shape.data[1] = 1;
	msg.ptr_shape.data[2] = 1;
	msg.ptr_shape.data[3] = 1;
	synthvid_send(hdev, &msg);

	return 0;
}