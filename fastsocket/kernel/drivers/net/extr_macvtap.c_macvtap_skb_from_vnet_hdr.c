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
struct virtio_net_hdr {int gso_type; scalar_t__ gso_size; int flags; int /*<<< orphan*/  csum_offset; int /*<<< orphan*/  csum_start; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ gso_size; unsigned short gso_type; scalar_t__ gso_segs; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short SKB_GSO_DODGY ; 
 unsigned short SKB_GSO_TCPV4 ; 
 unsigned short SKB_GSO_TCPV6 ; 
 unsigned short SKB_GSO_TCP_ECN ; 
 unsigned short SKB_GSO_UDP ; 
 int VIRTIO_NET_HDR_F_NEEDS_CSUM ; 
 int VIRTIO_NET_HDR_GSO_ECN ; 
 int VIRTIO_NET_HDR_GSO_NONE ; 
#define  VIRTIO_NET_HDR_GSO_TCPV4 130 
#define  VIRTIO_NET_HDR_GSO_TCPV6 129 
#define  VIRTIO_NET_HDR_GSO_UDP 128 
 int /*<<< orphan*/  skb_partial_csum_set (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int macvtap_skb_from_vnet_hdr(struct sk_buff *skb,
				     struct virtio_net_hdr *vnet_hdr)
{
	unsigned short gso_type = 0;
	if (vnet_hdr->gso_type != VIRTIO_NET_HDR_GSO_NONE) {
		switch (vnet_hdr->gso_type & ~VIRTIO_NET_HDR_GSO_ECN) {
		case VIRTIO_NET_HDR_GSO_TCPV4:
			gso_type = SKB_GSO_TCPV4;
			break;
		case VIRTIO_NET_HDR_GSO_TCPV6:
			gso_type = SKB_GSO_TCPV6;
			break;
		case VIRTIO_NET_HDR_GSO_UDP:
			gso_type = SKB_GSO_UDP;
			break;
		default:
			return -EINVAL;
		}

		if (vnet_hdr->gso_type & VIRTIO_NET_HDR_GSO_ECN)
			gso_type |= SKB_GSO_TCP_ECN;

		if (vnet_hdr->gso_size == 0)
			return -EINVAL;
	}

	if (vnet_hdr->flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) {
		if (!skb_partial_csum_set(skb, vnet_hdr->csum_start,
					  vnet_hdr->csum_offset))
			return -EINVAL;
	}

	if (vnet_hdr->gso_type != VIRTIO_NET_HDR_GSO_NONE) {
		skb_shinfo(skb)->gso_size = vnet_hdr->gso_size;
		skb_shinfo(skb)->gso_type = gso_type;

		/* Header must be checked, and gso_segs computed. */
		skb_shinfo(skb)->gso_type |= SKB_GSO_DODGY;
		skb_shinfo(skb)->gso_segs = 0;
	}
	return 0;
}