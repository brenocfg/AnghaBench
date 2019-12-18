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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  len; void* protocol; } ;
struct net_bridge {int multicast_last_member_interval; int multicast_query_response_interval; TYPE_1__* dev; } ;
struct iphdr {int version; int ihl; int tos; int ttl; int /*<<< orphan*/  daddr; scalar_t__ saddr; int /*<<< orphan*/  protocol; void* frag_off; scalar_t__ id; void* tot_len; } ;
struct igmphdr {int code; scalar_t__ csum; scalar_t__ group; int /*<<< orphan*/  type; } ;
struct ethhdr {int* h_dest; void* h_proto; int /*<<< orphan*/  h_source; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ETH_P_IP ; 
 int HZ ; 
 int /*<<< orphan*/  IGMP_HOST_MEMBERSHIP_QUERY ; 
 int IGMP_TIMER_SCALE ; 
 int /*<<< orphan*/  INADDR_ALLHOSTS_GROUP ; 
 int IPOPT_RA ; 
 int /*<<< orphan*/  IPPROTO_IGMP ; 
 int IP_DF ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 struct igmphdr* igmp_hdr (struct sk_buff*) ; 
 scalar_t__ ip_compute_csum (void*,int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *br_ip4_multicast_alloc_query(struct net_bridge *br,
						    __be32 group)
{
	struct sk_buff *skb;
	struct igmphdr *ih;
	struct ethhdr *eth;
	struct iphdr *iph;

	skb = netdev_alloc_skb_ip_align(br->dev, sizeof(*eth) + sizeof(*iph) +
						 sizeof(*ih) + 4);
	if (!skb)
		goto out;

	skb->protocol = htons(ETH_P_IP);

	skb_reset_mac_header(skb);
	eth = eth_hdr(skb);

	memcpy(eth->h_source, br->dev->dev_addr, 6);
	eth->h_dest[0] = 1;
	eth->h_dest[1] = 0;
	eth->h_dest[2] = 0x5e;
	eth->h_dest[3] = 0;
	eth->h_dest[4] = 0;
	eth->h_dest[5] = 1;
	eth->h_proto = htons(ETH_P_IP);
	skb_put(skb, sizeof(*eth));

	skb_set_network_header(skb, skb->len);
	iph = ip_hdr(skb);

	iph->version = 4;
	iph->ihl = 6;
	iph->tos = 0xc0;
	iph->tot_len = htons(sizeof(*iph) + sizeof(*ih) + 4);
	iph->id = 0;
	iph->frag_off = htons(IP_DF);
	iph->ttl = 1;
	iph->protocol = IPPROTO_IGMP;
	iph->saddr = 0;
	iph->daddr = htonl(INADDR_ALLHOSTS_GROUP);
	((u8 *)&iph[1])[0] = IPOPT_RA;
	((u8 *)&iph[1])[1] = 4;
	((u8 *)&iph[1])[2] = 0;
	((u8 *)&iph[1])[3] = 0;
	ip_send_check(iph);
	skb_put(skb, 24);

	skb_set_transport_header(skb, skb->len);
	ih = igmp_hdr(skb);
	ih->type = IGMP_HOST_MEMBERSHIP_QUERY;
	ih->code = (group ? br->multicast_last_member_interval :
			    br->multicast_query_response_interval) /
		   (HZ / IGMP_TIMER_SCALE);
	ih->group = group;
	ih->csum = 0;
	ih->csum = ip_compute_csum((void *)ih, sizeof(struct igmphdr));
	skb_put(skb, sizeof(*ih));

	__skb_pull(skb, sizeof(*eth));

out:
	return skb;
}