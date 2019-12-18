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
struct virtnet_info {int /*<<< orphan*/  rvq; int /*<<< orphan*/  dev; } ;
struct skb_vnet_hdr {int /*<<< orphan*/  hdr; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MAX_PACKET_LEN ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_to_sgvec (struct sk_buff*,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct skb_vnet_hdr* skb_vnet_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int virtqueue_add_buf (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int,struct sk_buff*) ; 

__attribute__((used)) static int add_recvbuf_small(struct virtnet_info *vi, gfp_t gfp)
{
	struct sk_buff *skb;
	struct skb_vnet_hdr *hdr;
	struct scatterlist sg[2];
	int err;

	skb = netdev_alloc_skb(vi->dev, MAX_PACKET_LEN + NET_IP_ALIGN);
	if (unlikely(!skb))
		return -ENOMEM;

	skb_reserve(skb, NET_IP_ALIGN);
	skb_put(skb, MAX_PACKET_LEN);

	hdr = skb_vnet_hdr(skb);
	sg_set_buf(sg, &hdr->hdr, sizeof hdr->hdr);

	skb_to_sgvec(skb, sg + 1, 0, skb->len);

	err = virtqueue_add_buf(vi->rvq, sg, 0, 2, skb);
	if (err < 0)
		dev_kfree_skb(skb);

	return err;
}