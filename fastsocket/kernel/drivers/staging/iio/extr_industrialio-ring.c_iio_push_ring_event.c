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
struct iio_ring_buffer {int /*<<< orphan*/  shared_ev_pointer; int /*<<< orphan*/  ev_int; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int __iio_push_event (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iio_push_ring_event(struct iio_ring_buffer *ring_buf,
		       int event_code,
		       s64 timestamp)
{
	return __iio_push_event(&ring_buf->ev_int,
			       event_code,
			       timestamp,
			       &ring_buf->shared_ev_pointer);
}