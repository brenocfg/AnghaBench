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
typedef  int u32 ;
typedef  int u16 ;
struct dvb_ringbuffer {int /*<<< orphan*/  queue; scalar_t__ pwrite; scalar_t__ pread; } ;

/* Variables and functions */
 int DVB_RINGBUFFER_PEEK (struct dvb_ringbuffer*,int) ; 
 int /*<<< orphan*/  DVB_RINGBUFFER_SKIP (struct dvb_ringbuffer*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,unsigned long,unsigned long) ; 
 int dvb_ringbuffer_avail (struct dvb_ringbuffer*) ; 
 int /*<<< orphan*/  dvb_ringbuffer_read (struct dvb_ringbuffer*,void*,size_t) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int av7110_pes_play(void *dest, struct dvb_ringbuffer *buf, int dlen)
{
	int len;
	u32 sync;
	u16 blen;

	if (!dlen) {
		wake_up(&buf->queue);
		return -1;
	}
	while (1) {
		len = dvb_ringbuffer_avail(buf);
		if (len < 6) {
			wake_up(&buf->queue);
			return -1;
		}
		sync =  DVB_RINGBUFFER_PEEK(buf, 0) << 24;
		sync |= DVB_RINGBUFFER_PEEK(buf, 1) << 16;
		sync |= DVB_RINGBUFFER_PEEK(buf, 2) << 8;
		sync |= DVB_RINGBUFFER_PEEK(buf, 3);

		if (((sync &~ 0x0f) == 0x000001e0) ||
		    ((sync &~ 0x1f) == 0x000001c0) ||
		    (sync == 0x000001bd))
			break;
		printk("resync\n");
		DVB_RINGBUFFER_SKIP(buf, 1);
	}
	blen =  DVB_RINGBUFFER_PEEK(buf, 4) << 8;
	blen |= DVB_RINGBUFFER_PEEK(buf, 5);
	blen += 6;
	if (len < blen || blen > dlen) {
		//printk("buffer empty - avail %d blen %u dlen %d\n", len, blen, dlen);
		wake_up(&buf->queue);
		return -1;
	}

	dvb_ringbuffer_read(buf, dest, (size_t) blen);

	dprintk(2, "pread=0x%08lx, pwrite=0x%08lx\n",
	       (unsigned long) buf->pread, (unsigned long) buf->pwrite);
	wake_up(&buf->queue);
	return blen;
}