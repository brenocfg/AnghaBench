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
struct video_mmap {size_t frame; } ;
struct cam_data {size_t curframe; TYPE_1__* frame; int /*<<< orphan*/  frame_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_READY ; 
 int allocate_frame_buf (struct cam_data*) ; 
 int fetch_frame (struct cam_data*) ; 

__attribute__((used)) static int capture_frame(struct cam_data *cam, struct video_mmap *vm)
{
	if (!cam->frame_buf) {
		/* we do lazy allocation */
		int err;
		if ((err = allocate_frame_buf(cam)))
			return err;
	}

	cam->curframe = vm->frame;
	cam->frame[cam->curframe].state = FRAME_READY;
	return fetch_frame(cam);
}