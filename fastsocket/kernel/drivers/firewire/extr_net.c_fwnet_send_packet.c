#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rfc2734_header {int /*<<< orphan*/  w1; int /*<<< orphan*/  w0; } ;
struct TYPE_7__ {int w0; int w1; } ;
struct fwnet_packet_task {unsigned int max_payload; scalar_t__ dest_node; int generation; unsigned long long fifo_addr; int /*<<< orphan*/  pt_link; TYPE_2__* skb; int /*<<< orphan*/  speed; int /*<<< orphan*/  transaction; TYPE_3__ hdr; struct fwnet_device* dev; } ;
struct fwnet_device {TYPE_1__* netdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  sent_list; TYPE_4__* card; int /*<<< orphan*/  broadcasted_list; } ;
struct TYPE_8__ {int generation; int node_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int IANA_SPECIFIER_ID ; 
 scalar_t__ IEEE1394_ALL_NODES ; 
 int /*<<< orphan*/  IEEE1394_BROADCAST_CHANNEL ; 
 int RFC2374_FRAG_HDR_SIZE ; 
#define  RFC2374_HDR_FIRSTFRAG 131 
#define  RFC2374_HDR_INTFRAG 130 
#define  RFC2374_HDR_LASTFRAG 129 
#define  RFC2374_HDR_UNFRAG 128 
 int RFC2374_UNFRAG_HDR_SIZE ; 
 int RFC2734_SW_VERSION ; 
 int /*<<< orphan*/  SCODE_100 ; 
 int /*<<< orphan*/  TCODE_STREAM_DATA ; 
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  fw_send_request (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct fwnet_packet_task*) ; 
 scalar_t__ fw_stream_packet_destination_id (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fwnet_get_hdr_lf (TYPE_3__*) ; 
 int /*<<< orphan*/  fwnet_write_complete ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_push (TYPE_2__*,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fwnet_send_packet(struct fwnet_packet_task *ptask)
{
	struct fwnet_device *dev;
	unsigned tx_len;
	struct rfc2734_header *bufhdr;
	unsigned long flags;

	dev = ptask->dev;
	tx_len = ptask->max_payload;
	switch (fwnet_get_hdr_lf(&ptask->hdr)) {
	case RFC2374_HDR_UNFRAG:
		bufhdr = (struct rfc2734_header *)
				skb_push(ptask->skb, RFC2374_UNFRAG_HDR_SIZE);
		put_unaligned_be32(ptask->hdr.w0, &bufhdr->w0);
		break;

	case RFC2374_HDR_FIRSTFRAG:
	case RFC2374_HDR_INTFRAG:
	case RFC2374_HDR_LASTFRAG:
		bufhdr = (struct rfc2734_header *)
				skb_push(ptask->skb, RFC2374_FRAG_HDR_SIZE);
		put_unaligned_be32(ptask->hdr.w0, &bufhdr->w0);
		put_unaligned_be32(ptask->hdr.w1, &bufhdr->w1);
		break;

	default:
		BUG();
	}
	if (ptask->dest_node == IEEE1394_ALL_NODES) {
		u8 *p;
		int generation;
		int node_id;

		/* ptask->generation may not have been set yet */
		generation = dev->card->generation;
		smp_rmb();
		node_id = dev->card->node_id;

		p = skb_push(ptask->skb, 8);
		put_unaligned_be32(node_id << 16 | IANA_SPECIFIER_ID >> 8, p);
		put_unaligned_be32((IANA_SPECIFIER_ID & 0xff) << 24
						| RFC2734_SW_VERSION, &p[4]);

		/* We should not transmit if broadcast_channel.valid == 0. */
		fw_send_request(dev->card, &ptask->transaction,
				TCODE_STREAM_DATA,
				fw_stream_packet_destination_id(3,
						IEEE1394_BROADCAST_CHANNEL, 0),
				generation, SCODE_100, 0ULL, ptask->skb->data,
				tx_len + 8, fwnet_write_complete, ptask);

		/* FIXME race? */
		spin_lock_irqsave(&dev->lock, flags);
		list_add_tail(&ptask->pt_link, &dev->broadcasted_list);
		spin_unlock_irqrestore(&dev->lock, flags);

		return 0;
	}

	fw_send_request(dev->card, &ptask->transaction,
			TCODE_WRITE_BLOCK_REQUEST, ptask->dest_node,
			ptask->generation, ptask->speed, ptask->fifo_addr,
			ptask->skb->data, tx_len, fwnet_write_complete, ptask);

	/* FIXME race? */
	spin_lock_irqsave(&dev->lock, flags);
	list_add_tail(&ptask->pt_link, &dev->sent_list);
	spin_unlock_irqrestore(&dev->lock, flags);

	dev->netdev->trans_start = jiffies;

	return 0;
}