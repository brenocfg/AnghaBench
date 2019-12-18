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
struct cam_data {scalar_t__ frame_buf; TYPE_1__* frame; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int CPIA_MAX_FRAME_SIZE ; 
 int ENOBUFS ; 
 int FRAME_NUM ; 
 scalar_t__ rvmalloc (int) ; 

__attribute__((used)) static int allocate_frame_buf(struct cam_data *cam)
{
	int i;

	cam->frame_buf = rvmalloc(FRAME_NUM * CPIA_MAX_FRAME_SIZE);
	if (!cam->frame_buf)
		return -ENOBUFS;

	for (i = 0; i < FRAME_NUM; i++)
		cam->frame[i].data = cam->frame_buf + i * CPIA_MAX_FRAME_SIZE;

	return 0;
}