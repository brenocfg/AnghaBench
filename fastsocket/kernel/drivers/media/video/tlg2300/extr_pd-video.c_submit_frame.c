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
struct videobuf_buffer {int /*<<< orphan*/  done; int /*<<< orphan*/  ts; int /*<<< orphan*/  field_count; int /*<<< orphan*/  state; } ;
struct front_face {struct videobuf_buffer* curr_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void submit_frame(struct front_face *front)
{
	struct videobuf_buffer *vb = front->curr_frame;

	if (vb == NULL)
		return;

	front->curr_frame	= NULL;
	vb->state		= VIDEOBUF_DONE;
	vb->field_count++;
	do_gettimeofday(&vb->ts);

	wake_up(&vb->done);
}