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
struct videobuf_queue {struct cx23885_tsport* priv_data; } ;
struct videobuf_buffer {int dummy; } ;
struct cx23885_tsport {int dummy; } ;
struct cx23885_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx23885_buf_queue (struct cx23885_tsport*,struct cx23885_buffer*) ; 

__attribute__((used)) static void dvb_buf_queue(struct videobuf_queue *q, struct videobuf_buffer *vb)
{
	struct cx23885_tsport *port = q->priv_data;
	cx23885_buf_queue(port, (struct cx23885_buffer *)vb);
}