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
struct videobuf_queue {int dummy; } ;
struct videobuf_buffer {int dummy; } ;
struct cx88_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx88_free_buffer (struct videobuf_queue*,struct cx88_buffer*) ; 

__attribute__((used)) static void dvb_buf_release(struct videobuf_queue *q,
			    struct videobuf_buffer *vb)
{
	cx88_free_buffer(q, (struct cx88_buffer*)vb);
}