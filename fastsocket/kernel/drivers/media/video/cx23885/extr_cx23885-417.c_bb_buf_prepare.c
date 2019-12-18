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
struct videobuf_queue {struct cx23885_fh* priv_data; } ;
struct videobuf_buffer {int dummy; } ;
struct cx23885_fh {TYPE_1__* dev; } ;
struct cx23885_buffer {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_2__ {int /*<<< orphan*/  ts1; } ;

/* Variables and functions */
 int cx23885_buf_prepare (struct videobuf_queue*,int /*<<< orphan*/ *,struct cx23885_buffer*,int) ; 

__attribute__((used)) static int bb_buf_prepare(struct videobuf_queue *q,
	struct videobuf_buffer *vb, enum v4l2_field field)
{
	struct cx23885_fh *fh = q->priv_data;
	return cx23885_buf_prepare(q, &fh->dev->ts1,
		(struct cx23885_buffer *)vb,
		field);
}