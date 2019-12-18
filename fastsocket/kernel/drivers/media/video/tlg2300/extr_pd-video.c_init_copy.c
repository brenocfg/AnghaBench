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
struct video_data {int field_count; char* dst; int lines_size; TYPE_1__* vbi; scalar_t__ prev_left; scalar_t__ lines_copied; struct front_face* front; } ;
struct front_face {int /*<<< orphan*/  curr_frame; } ;
struct TYPE_2__ {scalar_t__ copied; } ;

/* Variables and functions */
 scalar_t__ videobuf_to_vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_copy(struct video_data *video, bool index)
{
	struct front_face *front = video->front;

	video->field_count	= index;
	video->lines_copied	= 0;
	video->prev_left	= 0 ;
	video->dst 		= (char *)videobuf_to_vmalloc(front->curr_frame)
					+ index * video->lines_size;
	video->vbi->copied 	= 0; /* set it here */
}