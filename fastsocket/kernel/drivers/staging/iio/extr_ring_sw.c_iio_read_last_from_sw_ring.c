#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bpd; } ;
struct iio_sw_ring_buffer {unsigned char* last_written_p; TYPE_1__ buf; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  iio_mark_sw_rb_in_use (TYPE_1__*) ; 
 int /*<<< orphan*/  iio_unmark_sw_rb_in_use (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int iio_read_last_from_sw_ring(struct iio_sw_ring_buffer *ring,
			       unsigned char *data)
{
	unsigned char *last_written_p_copy;

	iio_mark_sw_rb_in_use(&ring->buf);
again:
	barrier();
	last_written_p_copy = ring->last_written_p;
	barrier(); /*unnessecary? */
	/* Check there is anything here */
	if (last_written_p_copy == 0)
		return -EAGAIN;
	memcpy(data, last_written_p_copy, ring->buf.bpd);

	if (unlikely(ring->last_written_p >= last_written_p_copy))
		goto again;

	iio_unmark_sw_rb_in_use(&ring->buf);
	return 0;
}