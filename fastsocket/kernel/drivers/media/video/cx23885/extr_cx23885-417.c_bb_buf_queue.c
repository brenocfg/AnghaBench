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
struct TYPE_2__ {int /*<<< orphan*/  ts1; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx23885_buf_queue (int /*<<< orphan*/ *,struct cx23885_buffer*) ; 

__attribute__((used)) static void bb_buf_queue(struct videobuf_queue *q,
	struct videobuf_buffer *vb)
{
	struct cx23885_fh *fh = q->priv_data;
	cx23885_buf_queue(&fh->dev->ts1, (struct cx23885_buffer *)vb);
}