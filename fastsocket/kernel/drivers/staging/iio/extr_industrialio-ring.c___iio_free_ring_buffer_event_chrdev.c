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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct iio_ring_buffer {TYPE_1__ ev_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_free_ev_int (TYPE_1__*) ; 
 int /*<<< orphan*/  iio_free_idr_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_ring_event_idr ; 

__attribute__((used)) static inline void
__iio_free_ring_buffer_event_chrdev(struct iio_ring_buffer *buf)
{
	iio_free_ev_int(&(buf->ev_int));
	iio_free_idr_val(&iio_ring_event_idr, buf->ev_int.id);
}