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
struct fwnet_device {unsigned long rcv_buffer_size; unsigned long broadcast_rcv_next_ptr; unsigned long num_broadcast_rcv_ptrs; int /*<<< orphan*/  lock; int /*<<< orphan*/  broadcast_rcv_buffer; int /*<<< orphan*/  broadcast_rcv_context; int /*<<< orphan*/ ** broadcast_rcv_buffer_ptrs; struct fw_card* card; } ;
struct fw_iso_packet {unsigned long payload_length; int interrupt; int tag; scalar_t__ header_length; scalar_t__ sy; scalar_t__ skip; } ;
struct fw_iso_context {int dummy; } ;
struct fw_card {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int IANA_SPECIFIER_ID ; 
 scalar_t__ IEEE1394_GASP_HDR_SIZE ; 
 int RFC2734_SW_VERSION ; 
 int be16_to_cpup (int /*<<< orphan*/ *) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_error (char*) ; 
 int fw_iso_context_queue (int /*<<< orphan*/ ,struct fw_iso_packet*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  fwnet_incoming_packet (struct fwnet_device*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fwnet_receive_broadcast(struct fw_iso_context *context,
		u32 cycle, size_t header_length, void *header, void *data)
{
	struct fwnet_device *dev;
	struct fw_iso_packet packet;
	struct fw_card *card;
	__be16 *hdr_ptr;
	__be32 *buf_ptr;
	int retval;
	u32 length;
	u16 source_node_id;
	u32 specifier_id;
	u32 ver;
	unsigned long offset;
	unsigned long flags;

	dev = data;
	card = dev->card;
	hdr_ptr = header;
	length = be16_to_cpup(hdr_ptr);

	spin_lock_irqsave(&dev->lock, flags);

	offset = dev->rcv_buffer_size * dev->broadcast_rcv_next_ptr;
	buf_ptr = dev->broadcast_rcv_buffer_ptrs[dev->broadcast_rcv_next_ptr++];
	if (dev->broadcast_rcv_next_ptr == dev->num_broadcast_rcv_ptrs)
		dev->broadcast_rcv_next_ptr = 0;

	spin_unlock_irqrestore(&dev->lock, flags);

	specifier_id =    (be32_to_cpu(buf_ptr[0]) & 0xffff) << 8
			| (be32_to_cpu(buf_ptr[1]) & 0xff000000) >> 24;
	ver = be32_to_cpu(buf_ptr[1]) & 0xffffff;
	source_node_id = be32_to_cpu(buf_ptr[0]) >> 16;

	if (specifier_id == IANA_SPECIFIER_ID && ver == RFC2734_SW_VERSION) {
		buf_ptr += 2;
		length -= IEEE1394_GASP_HDR_SIZE;
		fwnet_incoming_packet(dev, buf_ptr, length,
				      source_node_id, -1, true);
	}

	packet.payload_length = dev->rcv_buffer_size;
	packet.interrupt = 1;
	packet.skip = 0;
	packet.tag = 3;
	packet.sy = 0;
	packet.header_length = IEEE1394_GASP_HDR_SIZE;

	spin_lock_irqsave(&dev->lock, flags);

	retval = fw_iso_context_queue(dev->broadcast_rcv_context, &packet,
				      &dev->broadcast_rcv_buffer, offset);

	spin_unlock_irqrestore(&dev->lock, flags);

	if (retval < 0)
		fw_error("requeue failed\n");
}