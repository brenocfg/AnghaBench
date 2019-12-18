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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct iphdr {int frag_off; unsigned int protocol; int tot_len; int ihl; int saddr; int daddr; } ;
struct ethhdr {scalar_t__ h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int ETH_HLEN ; 
 int ETH_P_IP ; 
 unsigned int IPPROTO_TCP ; 
 unsigned int IPPROTO_UDP ; 
 int IP_MF ; 
 int IP_OFFSET ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int htons (int) ; 

__attribute__((used)) static void ioc3_tcpudp_checksum(struct sk_buff *skb, uint32_t hwsum, int len)
{
	struct ethhdr *eh = eth_hdr(skb);
	uint32_t csum, ehsum;
	unsigned int proto;
	struct iphdr *ih;
	uint16_t *ew;
	unsigned char *cp;

	/*
	 * Did hardware handle the checksum at all?  The cases we can handle
	 * are:
	 *
	 * - TCP and UDP checksums of IPv4 only.
	 * - IPv6 would be doable but we keep that for later ...
	 * - Only unfragmented packets.  Did somebody already tell you
	 *   fragmentation is evil?
	 * - don't care about packet size.  Worst case when processing a
	 *   malformed packet we'll try to access the packet at ip header +
	 *   64 bytes which is still inside the skb.  Even in the unlikely
	 *   case where the checksum is right the higher layers will still
	 *   drop the packet as appropriate.
	 */
	if (eh->h_proto != htons(ETH_P_IP))
		return;

	ih = (struct iphdr *) ((char *)eh + ETH_HLEN);
	if (ih->frag_off & htons(IP_MF | IP_OFFSET))
		return;

	proto = ih->protocol;
	if (proto != IPPROTO_TCP && proto != IPPROTO_UDP)
		return;

	/* Same as tx - compute csum of pseudo header  */
	csum = hwsum +
	       (ih->tot_len - (ih->ihl << 2)) +
	       htons((uint16_t)ih->protocol) +
	       (ih->saddr >> 16) + (ih->saddr & 0xffff) +
	       (ih->daddr >> 16) + (ih->daddr & 0xffff);

	/* Sum up ethernet dest addr, src addr and protocol  */
	ew = (uint16_t *) eh;
	ehsum = ew[0] + ew[1] + ew[2] + ew[3] + ew[4] + ew[5] + ew[6];

	ehsum = (ehsum & 0xffff) + (ehsum >> 16);
	ehsum = (ehsum & 0xffff) + (ehsum >> 16);

	csum += 0xffff ^ ehsum;

	/* In the next step we also subtract the 1's complement
	   checksum of the trailing ethernet CRC.  */
	cp = (char *)eh + len;	/* points at trailing CRC */
	if (len & 1) {
		csum += 0xffff ^ (uint16_t) ((cp[1] << 8) | cp[0]);
		csum += 0xffff ^ (uint16_t) ((cp[3] << 8) | cp[2]);
	} else {
		csum += 0xffff ^ (uint16_t) ((cp[0] << 8) | cp[1]);
		csum += 0xffff ^ (uint16_t) ((cp[2] << 8) | cp[3]);
	}

	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);

	if (csum == 0xffff)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
}