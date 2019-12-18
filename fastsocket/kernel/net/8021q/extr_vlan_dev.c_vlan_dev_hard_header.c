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
typedef  unsigned int u16 ;
struct vlan_hdr {void* h_vlan_encapsulated_proto; void* h_vlan_TCI; } ;
struct sk_buff {void* protocol; } ;
struct net_device {scalar_t__ hard_header_len; void* dev_addr; } ;
struct TYPE_2__ {int flags; unsigned int vlan_id; struct net_device* real_dev; } ;

/* Variables and functions */
 int ENOSPC ; 
 unsigned int ETH_P_8021Q ; 
 unsigned short ETH_P_802_3 ; 
 int VLAN_FLAG_REORDER_HDR ; 
 unsigned int VLAN_HLEN ; 
 scalar_t__ WARN_ON (int) ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,unsigned short,void const*,void const*,unsigned int) ; 
 void* htons (unsigned int) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_push (struct sk_buff*,unsigned int) ; 
 unsigned int vlan_dev_get_egress_qos_mask (struct net_device*,struct sk_buff*) ; 
 TYPE_1__* vlan_dev_info (struct net_device*) ; 

__attribute__((used)) static int vlan_dev_hard_header(struct sk_buff *skb, struct net_device *dev,
				unsigned short type,
				const void *daddr, const void *saddr,
				unsigned int len)
{
	struct vlan_hdr *vhdr;
	unsigned int vhdrlen = 0;
	u16 vlan_tci = 0;
	int rc;

	if (WARN_ON(skb_headroom(skb) < dev->hard_header_len))
		return -ENOSPC;

	if (!(vlan_dev_info(dev)->flags & VLAN_FLAG_REORDER_HDR)) {
		vhdr = (struct vlan_hdr *) skb_push(skb, VLAN_HLEN);

		vlan_tci = vlan_dev_info(dev)->vlan_id;
		vlan_tci |= vlan_dev_get_egress_qos_mask(dev, skb);
		vhdr->h_vlan_TCI = htons(vlan_tci);

		/*
		 *  Set the protocol type. For a packet of type ETH_P_802_3 we
		 *  put the length in here instead. It is up to the 802.2
		 *  layer to carry protocol information.
		 */
		if (type != ETH_P_802_3)
			vhdr->h_vlan_encapsulated_proto = htons(type);
		else
			vhdr->h_vlan_encapsulated_proto = htons(len);

		skb->protocol = htons(ETH_P_8021Q);
		type = ETH_P_8021Q;
		vhdrlen = VLAN_HLEN;
	}

	/* Before delegating work to the lower layer, enter our MAC-address */
	if (saddr == NULL)
		saddr = dev->dev_addr;

	/* Now make the underlying real hard header */
	dev = vlan_dev_info(dev)->real_dev;
	rc = dev_hard_header(skb, dev, type, daddr, saddr, len + vhdrlen);
	if (rc > 0)
		rc += vhdrlen;
	return rc;
}