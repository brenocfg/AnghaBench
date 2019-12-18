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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_ringbuffer {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int dvb_ringbuffer_free (struct dvb_ringbuffer*) ; 
 int /*<<< orphan*/  dvb_ringbuffer_write (struct dvb_ringbuffer*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline long aux_ring_buffer_write(struct dvb_ringbuffer *rbuf,
					 const u8 *buf, unsigned long count)
{
	unsigned long todo = count;
	int free;

	while (todo > 0) {
		if (dvb_ringbuffer_free(rbuf) < 2048) {
			if (wait_event_interruptible(rbuf->queue,
						     (dvb_ringbuffer_free(rbuf) >= 2048)))
				return count - todo;
		}
		free = dvb_ringbuffer_free(rbuf);
		if (free > todo)
			free = todo;
		dvb_ringbuffer_write(rbuf, buf, free);
		todo -= free;
		buf += free;
	}

	return count - todo;
}