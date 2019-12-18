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
struct xdr_skb_reader {int offset; int count; int /*<<< orphan*/  csum; struct sk_buff* skb; } ;
struct xdr_buf {int dummy; } ;
struct udphdr {int dummy; } ;
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  dev; int /*<<< orphan*/  csum; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  csum_block_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_rx_csum_fault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_csum_unnecessary (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xdr_partial_copy_from_skb (struct xdr_buf*,int /*<<< orphan*/ ,struct xdr_skb_reader*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_skb_read_and_csum_bits ; 
 int /*<<< orphan*/  xdr_skb_read_bits ; 

int csum_partial_copy_to_xdr(struct xdr_buf *xdr, struct sk_buff *skb)
{
	struct xdr_skb_reader	desc;

	desc.skb = skb;
	desc.offset = sizeof(struct udphdr);
	desc.count = skb->len - desc.offset;

	if (skb_csum_unnecessary(skb))
		goto no_checksum;

	desc.csum = csum_partial(skb->data, desc.offset, skb->csum);
	if (xdr_partial_copy_from_skb(xdr, 0, &desc, xdr_skb_read_and_csum_bits) < 0)
		return -1;
	if (desc.offset != skb->len) {
		__wsum csum2;
		csum2 = skb_checksum(skb, desc.offset, skb->len - desc.offset, 0);
		desc.csum = csum_block_add(desc.csum, csum2, desc.offset);
	}
	if (desc.count)
		return -1;
	if (csum_fold(desc.csum))
		return -1;
	if (unlikely(skb->ip_summed == CHECKSUM_COMPLETE))
		netdev_rx_csum_fault(skb->dev);
	return 0;
no_checksum:
	if (xdr_partial_copy_from_skb(xdr, 0, &desc, xdr_skb_read_bits) < 0)
		return -1;
	if (desc.count)
		return -1;
	return 0;
}