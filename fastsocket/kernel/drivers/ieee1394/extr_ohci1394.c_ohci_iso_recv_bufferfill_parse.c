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
struct ti_ohci {int dummy; } ;
struct ohci_iso_recv {unsigned int dma_offset; unsigned int buf_stride; unsigned int block_dma; int nblocks; struct ti_ohci* ohci; } ;
struct TYPE_2__ {unsigned char* kvirt; } ;
struct hpsb_iso {TYPE_1__ data_buf; int /*<<< orphan*/  overflows; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpsb_iso_packet_received (struct hpsb_iso*,unsigned int,unsigned short,unsigned short,unsigned short,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  hpsb_iso_wake (struct hpsb_iso*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void ohci_iso_recv_bufferfill_parse(struct hpsb_iso *iso, struct ohci_iso_recv *recv)
{
	int wake = 0;
	int runaway = 0;
	struct ti_ohci *ohci = recv->ohci;

	while (1) {
		/* we expect the next parsable packet to begin at recv->dma_offset */
		/* note: packet layout is as shown in section 10.6.1.1 of the OHCI spec */

		unsigned int offset;
		unsigned short len, cycle, total_len;
		unsigned char channel, tag, sy;

		unsigned char *p = iso->data_buf.kvirt;

		unsigned int this_block = recv->dma_offset/recv->buf_stride;

		/* don't loop indefinitely */
		if (runaway++ > 100000) {
			atomic_inc(&iso->overflows);
			PRINT(KERN_ERR,
			      "IR DMA error - Runaway during buffer parsing!\n");
			break;
		}

		/* stop parsing once we arrive at block_dma (i.e. don't get ahead of DMA) */
		if (this_block == recv->block_dma)
			break;

		wake = 1;

		/* parse data length, tag, channel, and sy */

		/* note: we keep our own local copies of 'len' and 'offset'
		   so the user can't mess with them by poking in the mmap area */

		len = p[recv->dma_offset+2] | (p[recv->dma_offset+3] << 8);

		if (len > 4096) {
			PRINT(KERN_ERR,
			      "IR DMA error - bogus 'len' value %u\n", len);
		}

		channel = p[recv->dma_offset+1] & 0x3F;
		tag = p[recv->dma_offset+1] >> 6;
		sy = p[recv->dma_offset+0] & 0xF;

		/* advance to data payload */
		recv->dma_offset += 4;

		/* check for wrap-around */
		if (recv->dma_offset >= recv->buf_stride*recv->nblocks) {
			recv->dma_offset -= recv->buf_stride*recv->nblocks;
		}

		/* dma_offset now points to the first byte of the data payload */
		offset = recv->dma_offset;

		/* advance to xferStatus/timeStamp */
		recv->dma_offset += len;

		total_len = len + 8; /* 8 bytes header+trailer in OHCI packet */
		/* payload is padded to 4 bytes */
		if (len % 4) {
			recv->dma_offset += 4 - (len%4);
			total_len += 4 - (len%4);
		}

		/* check for wrap-around */
		if (recv->dma_offset >= recv->buf_stride*recv->nblocks) {
			/* uh oh, the packet data wraps from the last
                           to the first DMA block - make the packet
                           contiguous by copying its "tail" into the
                           guard page */

			int guard_off = recv->buf_stride*recv->nblocks;
			int tail_len = len - (guard_off - offset);

			if (tail_len > 0  && tail_len < recv->buf_stride) {
				memcpy(iso->data_buf.kvirt + guard_off,
				       iso->data_buf.kvirt,
				       tail_len);
			}

			recv->dma_offset -= recv->buf_stride*recv->nblocks;
		}

		/* parse timestamp */
		cycle = p[recv->dma_offset+0] | (p[recv->dma_offset+1]<<8);
		cycle &= 0x1FFF;

		/* advance to next packet */
		recv->dma_offset += 4;

		/* check for wrap-around */
		if (recv->dma_offset >= recv->buf_stride*recv->nblocks) {
			recv->dma_offset -= recv->buf_stride*recv->nblocks;
		}

		hpsb_iso_packet_received(iso, offset, len, total_len, cycle, channel, tag, sy);
	}

	if (wake)
		hpsb_iso_wake(iso);
}