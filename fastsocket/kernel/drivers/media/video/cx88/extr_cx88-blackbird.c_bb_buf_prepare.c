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
struct videobuf_queue {struct cx8802_fh* priv_data; } ;
struct videobuf_buffer {int dummy; } ;
struct cx88_buffer {int dummy; } ;
struct cx8802_fh {int /*<<< orphan*/  dev; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int cx8802_buf_prepare (struct videobuf_queue*,int /*<<< orphan*/ ,struct cx88_buffer*,int) ; 

__attribute__((used)) static int
bb_buf_prepare(struct videobuf_queue *q, struct videobuf_buffer *vb,
	       enum v4l2_field field)
{
	struct cx8802_fh *fh = q->priv_data;
	return cx8802_buf_prepare(q, fh->dev, (struct cx88_buffer*)vb, field);
}