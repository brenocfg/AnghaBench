#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int length; int bpd; TYPE_2__ shared_ev_pointer; int /*<<< orphan*/  ev_int; } ;
struct iio_sw_ring_buffer {unsigned char* write_p; unsigned char* data; unsigned char* half_p; unsigned char* last_written_p; unsigned char* read_p; TYPE_1__ buf; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_EVENT_CODE_RING_100_FULL ; 
 int IIO_EVENT_CODE_RING_50_FULL ; 
 int __iio_push_event (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  barrier () ; 
 int iio_push_or_escallate_ring_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int iio_store_to_sw_ring(struct iio_sw_ring_buffer *ring,
			 unsigned char *data,
			 s64 timestamp)
{
	int ret = 0;
	int code;
	unsigned char *temp_ptr, *change_test_ptr;

	/* initial store */
	if (unlikely(ring->write_p == 0)) {
		ring->write_p = ring->data;
		/* Doesn't actually matter if this is out of the set
		 * as long as the read pointer is valid before this
		 * passes it - guaranteed as set later in this function.
		 */
		ring->half_p = ring->data - ring->buf.length*ring->buf.bpd/2;
	}
	/* Copy data to where ever the current write pointer says */
	memcpy(ring->write_p, data, ring->buf.bpd);
	barrier();
	/* Update the pointer used to get most recent value.
	 * Always valid as either points to latest or second latest value.
	 * Before this runs it is null and read attempts fail with -EAGAIN.
	 */
	ring->last_written_p = ring->write_p;
	barrier();
	/* temp_ptr used to ensure we never have an invalid pointer
	 * it may be slightly lagging, but never invalid
	 */
	temp_ptr = ring->write_p + ring->buf.bpd;
	/* End of ring, back to the beginning */
	if (temp_ptr == ring->data + ring->buf.length*ring->buf.bpd)
		temp_ptr = ring->data;
	/* Update the write pointer
	 * always valid as long as this is the only function able to write.
	 * Care needed with smp systems to ensure more than one ring fill
	 * is never scheduled.
	 */
	ring->write_p = temp_ptr;

	if (ring->read_p == 0)
		ring->read_p = ring->data;
	/* Buffer full - move the read pointer and create / escalate
	 * ring event */
	/* Tricky case - if the read pointer moves before we adjust it.
	 * Handle by not pushing if it has moved - may result in occasional
	 * unnecessary buffer full events when it wasn't quite true.
	 */
	else if (ring->write_p == ring->read_p) {
		change_test_ptr = ring->read_p;
		temp_ptr = change_test_ptr + ring->buf.bpd;
		if (temp_ptr
		    == ring->data + ring->buf.length*ring->buf.bpd) {
			temp_ptr = ring->data;
		}
		/* We are moving pointer on one because the ring is full.  Any
		 * change to the read pointer will be this or greater.
		 */
		if (change_test_ptr == ring->read_p)
			ring->read_p = temp_ptr;

		spin_lock(&ring->buf.shared_ev_pointer.lock);

		ret = iio_push_or_escallate_ring_event(&ring->buf,
						       IIO_EVENT_CODE_RING_100_FULL,
						       timestamp);
		spin_unlock(&ring->buf.shared_ev_pointer.lock);
		if (ret)
			goto error_ret;
	}
	/* investigate if our event barrier has been passed */
	/* There are definite 'issues' with this and chances of
	 * simultaneous read */
	/* Also need to use loop count to ensure this only happens once */
	ring->half_p += ring->buf.bpd;
	if (ring->half_p == ring->data + ring->buf.length*ring->buf.bpd)
		ring->half_p = ring->data;
	if (ring->half_p == ring->read_p) {
		spin_lock(&ring->buf.shared_ev_pointer.lock);
		code = IIO_EVENT_CODE_RING_50_FULL;
		ret = __iio_push_event(&ring->buf.ev_int,
				       code,
				       timestamp,
				       &ring->buf.shared_ev_pointer);
		spin_unlock(&ring->buf.shared_ev_pointer.lock);
	}
error_ret:
	return ret;
}