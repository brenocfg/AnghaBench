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
struct dvb_ringbuffer {size_t* data; size_t size; } ;

/* Variables and functions */
 size_t DVB_RINGBUFFER_PEEK (struct dvb_ringbuffer*,int) ; 
 scalar_t__ DVB_RINGBUFFER_PKTHDRSIZE ; 
 int /*<<< orphan*/  DVB_RINGBUFFER_SKIP (struct dvb_ringbuffer*,scalar_t__) ; 
 size_t PKT_DISPOSED ; 
 scalar_t__ dvb_ringbuffer_avail (struct dvb_ringbuffer*) ; 

void dvb_ringbuffer_pkt_dispose(struct dvb_ringbuffer *rbuf, size_t idx)
{
	size_t pktlen;

	rbuf->data[(idx + 2) % rbuf->size] = PKT_DISPOSED;

	// clean up disposed packets
	while(dvb_ringbuffer_avail(rbuf) > DVB_RINGBUFFER_PKTHDRSIZE) {
		if (DVB_RINGBUFFER_PEEK(rbuf, 2) == PKT_DISPOSED) {
			pktlen = DVB_RINGBUFFER_PEEK(rbuf, 0) << 8;
			pktlen |= DVB_RINGBUFFER_PEEK(rbuf, 1);
			DVB_RINGBUFFER_SKIP(rbuf, pktlen + DVB_RINGBUFFER_PKTHDRSIZE);
		} else {
			// first packet is not disposed, so we stop cleaning now
			break;
		}
	}
}