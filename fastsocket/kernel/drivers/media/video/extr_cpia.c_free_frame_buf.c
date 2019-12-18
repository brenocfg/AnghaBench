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
struct cam_data {TYPE_1__* frame; int /*<<< orphan*/ * frame_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int CPIA_MAX_FRAME_SIZE ; 
 int FRAME_NUM ; 
 int /*<<< orphan*/  rvfree (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int free_frame_buf(struct cam_data *cam)
{
	int i;

	rvfree(cam->frame_buf, FRAME_NUM*CPIA_MAX_FRAME_SIZE);
	cam->frame_buf = NULL;
	for (i=0; i < FRAME_NUM; i++)
		cam->frame[i].data = NULL;

	return 0;
}