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
typedef  int /*<<< orphan*/  vnet_hdr ;
struct virtio_net_hdr {int flags; unsigned long csum_start; unsigned long csum_offset; unsigned long hdr_len; int /*<<< orphan*/  member_0; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct msghdr {scalar_t__ msg_control; } ;
struct macvtap_queue {int flags; int vnet_hdr_sz; int /*<<< orphan*/  vlan; int /*<<< orphan*/  sk; } ;
struct macvlan_dev {int /*<<< orphan*/  dev; } ;
struct iovec {int dummy; } ;
typedef  unsigned long ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  h_proto; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_6__ {scalar_t__ destructor_arg; } ;
struct TYPE_5__ {int dev_zerocopy; int shared_frag; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 unsigned long ETH_HLEN ; 
 int GOODCOPY_LEN ; 
 int IFF_VNET_HDR ; 
 size_t MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int /*<<< orphan*/  SOCK_ZEROCOPY ; 
 size_t UIO_MAXIOV ; 
 int VIRTIO_NET_HDR_F_NEEDS_CSUM ; 
 TYPE_4__* eth_hdr (struct sk_buff*) ; 
 int iov_length (struct iovec const*,size_t) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  macvlan_start_xmit (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* macvtap_alloc_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int macvtap_skb_from_vnet_hdr (struct sk_buff*,struct virtio_net_hdr*) ; 
 int memcpy_fromiovecend (void*,struct iovec const*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct macvlan_dev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int skb_copy_datagram_from_iovec (struct sk_buff*,int /*<<< orphan*/ ,struct iovec const*,int,unsigned long) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,unsigned long) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 TYPE_1__* skb_tx (struct sk_buff*) ; 
 scalar_t__ sock_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int zerocopy_sg_from_iovec (struct sk_buff*,struct iovec const*,int,size_t) ; 

__attribute__((used)) static ssize_t macvtap_get_user(struct macvtap_queue *q, struct msghdr *m,
				const struct iovec *iv, unsigned long total_len,
				size_t count, int noblock)
{
	struct sk_buff *skb;
	struct macvlan_dev *vlan;
	unsigned long len = total_len;
	int err;
	struct virtio_net_hdr vnet_hdr = { 0 };
	int vnet_hdr_len = 0;
	int copylen = 0;
	bool zerocopy = false;

	if (q->flags & IFF_VNET_HDR) {
		vnet_hdr_len = q->vnet_hdr_sz;

		err = -EINVAL;
		if ((len -= vnet_hdr_len) < 0)
			goto err;

		err = memcpy_fromiovecend((void *)&vnet_hdr, iv, 0,
					   sizeof(vnet_hdr));
		if (err < 0)
			goto err;
		if ((vnet_hdr.flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) &&
		     vnet_hdr.csum_start + vnet_hdr.csum_offset + 2 >
							vnet_hdr.hdr_len)
			vnet_hdr.hdr_len = vnet_hdr.csum_start +
						vnet_hdr.csum_offset + 2;
		err = -EINVAL;
		if (vnet_hdr.hdr_len > len)
			goto err;
	}

	err = -EINVAL;
	if (unlikely(len < ETH_HLEN))
		goto err;

	err = -EMSGSIZE;
	if (unlikely(count > UIO_MAXIOV))
		goto err;

	if (m && m->msg_control && sock_flag(&q->sk, SOCK_ZEROCOPY))
		zerocopy = true;

	if (zerocopy) {
		/* Userspace may produce vectors with count greater than
		 * MAX_SKB_FRAGS, so we need to linearize parts of the skb
		 * to let the rest of data to be fit in the frags.
		 */
		if (count > MAX_SKB_FRAGS) {
			copylen = iov_length(iv, count - MAX_SKB_FRAGS);
			if (copylen < vnet_hdr_len)
				copylen = 0;
			else
				copylen -= vnet_hdr_len;
		}
		/* There are 256 bytes to be copied in skb, so there is enough
		 * room for skb expand head in case it is used.
		 * The rest buffer is mapped from userspace.
		 */
		if (copylen < vnet_hdr.hdr_len)
			copylen = vnet_hdr.hdr_len;
		if (!copylen)
			copylen = GOODCOPY_LEN;
	} else
		copylen = len;

	skb = macvtap_alloc_skb(&q->sk, NET_IP_ALIGN, copylen,
				vnet_hdr.hdr_len, noblock, &err);
	if (!skb)
		goto err;

	if (zerocopy)
		err = zerocopy_sg_from_iovec(skb, iv, vnet_hdr_len, count);
	else
		err = skb_copy_datagram_from_iovec(skb, 0, iv, vnet_hdr_len,
						   len);
	if (err)
		goto err_kfree;

	skb_set_network_header(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;

	if (vnet_hdr_len) {
		err = macvtap_skb_from_vnet_hdr(skb, &vnet_hdr);
		if (err)
			goto err_kfree;
	}

	rcu_read_lock();
	vlan = rcu_dereference(q->vlan);
	/* copy skb_ubuf_info for callback when skb has no error */
	if (zerocopy) {
		skb_shinfo(skb)->destructor_arg = m->msg_control;
		skb_tx(skb)->dev_zerocopy = 1;
		skb_tx(skb)->shared_frag = 1;
	}
	if (vlan)
		macvlan_start_xmit(skb, vlan->dev);
	else
		kfree_skb(skb);
	rcu_read_unlock();

	return total_len;

err_kfree:
	kfree_skb(skb);

err:
	rcu_read_lock();
	vlan = rcu_dereference(q->vlan);
	if (vlan)
		netdev_get_tx_queue(vlan->dev, 0)->tx_dropped++;
	rcu_read_unlock();

	return err;
}