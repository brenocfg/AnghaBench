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
struct sk_buff {int /*<<< orphan*/  len; void* protocol; struct net_device* dev; } ;
struct net_device {unsigned char* dev_addr; unsigned char* broadcast; int type; int addr_len; } ;
struct arphdr {int ar_hln; int ar_pln; void* ar_op; void* ar_pro; void* ar_hrd; } ;
typedef  unsigned char const __be32 ;

/* Variables and functions */
#define  ARPHRD_AX25 131 
 int ARPHRD_ETHER ; 
#define  ARPHRD_FDDI 130 
 int ARPHRD_IEEE802 ; 
#define  ARPHRD_IEEE802_TR 129 
#define  ARPHRD_NETROM 128 
 int AX25_P_IP ; 
 int ETH_P_ARP ; 
 int ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ LL_ALLOCATED_SPACE (struct net_device*) ; 
 int /*<<< orphan*/  LL_RESERVED_SPACE (struct net_device*) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ arp_hdr_len (struct net_device*) ; 
 scalar_t__ dev_hard_header (struct sk_buff*,struct net_device*,int,unsigned char const*,unsigned char const*,int /*<<< orphan*/ ) ; 
 void* htons (int const) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

struct sk_buff *arp_create(int type, int ptype, __be32 dest_ip,
			   struct net_device *dev, __be32 src_ip,
			   const unsigned char *dest_hw,
			   const unsigned char *src_hw,
			   const unsigned char *target_hw)
{
	struct sk_buff *skb;
	struct arphdr *arp;
	unsigned char *arp_ptr;

	/*
	 *	Allocate a buffer
	 */

	skb = alloc_skb(arp_hdr_len(dev) + LL_ALLOCATED_SPACE(dev), GFP_ATOMIC);
	if (skb == NULL)
		return NULL;

	skb_reserve(skb, LL_RESERVED_SPACE(dev));
	skb_reset_network_header(skb);
	arp = (struct arphdr *) skb_put(skb, arp_hdr_len(dev));
	skb->dev = dev;
	skb->protocol = htons(ETH_P_ARP);
	if (src_hw == NULL)
		src_hw = dev->dev_addr;
	if (dest_hw == NULL)
		dest_hw = dev->broadcast;

	/*
	 *	Fill the device header for the ARP frame
	 */
	if (dev_hard_header(skb, dev, ptype, dest_hw, src_hw, skb->len) < 0)
		goto out;

	/*
	 * Fill out the arp protocol part.
	 *
	 * The arp hardware type should match the device type, except for FDDI,
	 * which (according to RFC 1390) should always equal 1 (Ethernet).
	 */
	/*
	 *	Exceptions everywhere. AX.25 uses the AX.25 PID value not the
	 *	DIX code for the protocol. Make these device structure fields.
	 */
	switch (dev->type) {
	default:
		arp->ar_hrd = htons(dev->type);
		arp->ar_pro = htons(ETH_P_IP);
		break;

#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
	case ARPHRD_AX25:
		arp->ar_hrd = htons(ARPHRD_AX25);
		arp->ar_pro = htons(AX25_P_IP);
		break;

#if defined(CONFIG_NETROM) || defined(CONFIG_NETROM_MODULE)
	case ARPHRD_NETROM:
		arp->ar_hrd = htons(ARPHRD_NETROM);
		arp->ar_pro = htons(AX25_P_IP);
		break;
#endif
#endif

#ifdef CONFIG_FDDI
	case ARPHRD_FDDI:
		arp->ar_hrd = htons(ARPHRD_ETHER);
		arp->ar_pro = htons(ETH_P_IP);
		break;
#endif
#ifdef CONFIG_TR
	case ARPHRD_IEEE802_TR:
		arp->ar_hrd = htons(ARPHRD_IEEE802);
		arp->ar_pro = htons(ETH_P_IP);
		break;
#endif
	}

	arp->ar_hln = dev->addr_len;
	arp->ar_pln = 4;
	arp->ar_op = htons(type);

	arp_ptr=(unsigned char *)(arp+1);

	memcpy(arp_ptr, src_hw, dev->addr_len);
	arp_ptr += dev->addr_len;
	memcpy(arp_ptr, &src_ip, 4);
	arp_ptr += 4;
	if (target_hw != NULL)
		memcpy(arp_ptr, target_hw, dev->addr_len);
	else
		memset(arp_ptr, 0, dev->addr_len);
	arp_ptr += dev->addr_len;
	memcpy(arp_ptr, &dest_ip, 4);

	return skb;

out:
	kfree_skb(skb);
	return NULL;
}