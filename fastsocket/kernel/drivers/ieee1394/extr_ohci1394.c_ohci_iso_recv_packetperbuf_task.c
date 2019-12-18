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
typedef  int u32 ;
typedef  int u16 ;
struct ti_ohci {int dummy; } ;
struct TYPE_3__ {scalar_t__ kvirt; } ;
struct ohci_iso_recv {int nblocks; int buf_stride; unsigned int block_dma; TYPE_1__ prog; struct ti_ohci* ohci; } ;
struct TYPE_4__ {unsigned char* kvirt; } ;
struct hpsb_iso {int pkt_dma; TYPE_2__ data_buf; } ;
struct dma_cmd {unsigned int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_region_sync_for_cpu (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  hpsb_iso_packet_received (struct hpsb_iso*,unsigned int,int,unsigned int,unsigned short,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  hpsb_iso_wake (struct hpsb_iso*) ; 
 int le32_to_cpu (unsigned int) ; 

__attribute__((used)) static void ohci_iso_recv_packetperbuf_task(struct hpsb_iso *iso, struct ohci_iso_recv *recv)
{
	int count;
	int wake = 0;
	struct ti_ohci *ohci = recv->ohci;

	/* loop over the entire buffer */
	for (count = 0; count < recv->nblocks; count++) {
		u32 packet_len = 0;

		/* pointer to the DMA descriptor */
		struct dma_cmd *il = ((struct dma_cmd*) recv->prog.kvirt) + iso->pkt_dma;

		/* check the DMA descriptor for new writes to xferStatus */
		u16 xferstatus = le32_to_cpu(il->status) >> 16;
		u16 rescount = le32_to_cpu(il->status) & 0xFFFF;

		unsigned char event = xferstatus & 0x1F;

		if (!event) {
			/* this packet hasn't come in yet; we are done for now */
			goto out;
		}

		if (event == 0x11) {
			/* packet received successfully! */

			/* rescount is the number of bytes *remaining* in the packet buffer,
			   after the packet was written */
			packet_len = recv->buf_stride - rescount;

		} else if (event == 0x02) {
			PRINT(KERN_ERR, "IR DMA error - packet too long for buffer\n");
		} else if (event) {
			PRINT(KERN_ERR, "IR DMA error - OHCI error code 0x%02x\n", event);
		}

		/* sync our view of the buffer */
		dma_region_sync_for_cpu(&iso->data_buf, iso->pkt_dma * recv->buf_stride, recv->buf_stride);

		/* record the per-packet info */
		{
			/* iso header is 8 bytes ahead of the data payload */
			unsigned char *hdr;

			unsigned int offset;
			unsigned short cycle;
			unsigned char channel, tag, sy;

			offset = iso->pkt_dma * recv->buf_stride;
			hdr = iso->data_buf.kvirt + offset;

			/* skip iso header */
			offset += 8;
			packet_len -= 8;

			cycle = (hdr[0] | (hdr[1] << 8)) & 0x1FFF;
			channel = hdr[5] & 0x3F;
			tag = hdr[5] >> 6;
			sy = hdr[4] & 0xF;

			hpsb_iso_packet_received(iso, offset, packet_len,
					recv->buf_stride, cycle, channel, tag, sy);
		}

		/* reset the DMA descriptor */
		il->status = recv->buf_stride;

		wake = 1;
		recv->block_dma = iso->pkt_dma;
	}

out:
	if (wake)
		hpsb_iso_wake(iso);
}