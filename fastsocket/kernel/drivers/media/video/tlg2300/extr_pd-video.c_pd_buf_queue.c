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
struct videobuf_queue {struct front_face* priv_data; } ;
struct videobuf_buffer {int /*<<< orphan*/  queue; int /*<<< orphan*/  state; } ;
struct front_face {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_QUEUED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pd_buf_queue(struct videobuf_queue *q, struct videobuf_buffer *vb)
{
	struct front_face *front = q->priv_data;
	vb->state = VIDEOBUF_QUEUED;
	list_add_tail(&vb->queue, &front->active);
}