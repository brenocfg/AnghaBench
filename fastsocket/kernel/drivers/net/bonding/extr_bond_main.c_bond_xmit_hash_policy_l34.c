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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int protocol; scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct iphdr {int ihl; int frag_off; scalar_t__ protocol; int saddr; int daddr; } ;
struct ethhdr {int* h_dest; int* h_source; } ;
typedef  int __be16 ;

/* Variables and functions */
 int ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int IP_MF ; 
 int IP_OFFSET ; 
 int htons (int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ntohl (int) ; 
 int ntohs (int) ; 

__attribute__((used)) static int bond_xmit_hash_policy_l34(struct sk_buff *skb,
				    struct net_device *bond_dev, int count)
{
	struct ethhdr *data = (struct ethhdr *)skb->data;
	struct iphdr *iph = ip_hdr(skb);
	__be16 *layer4hdr = (__be16 *)((u32 *)iph + iph->ihl);
	int layer4_xor = 0;

	if (skb->protocol == htons(ETH_P_IP)) {
		if (!(iph->frag_off & htons(IP_MF|IP_OFFSET)) &&
		    (iph->protocol == IPPROTO_TCP ||
		     iph->protocol == IPPROTO_UDP)) {
			layer4_xor = ntohs((*layer4hdr ^ *(layer4hdr + 1)));
		}
		return (layer4_xor ^
			((ntohl(iph->saddr ^ iph->daddr)) & 0xffff)) % count;

	}

	return (data->h_dest[5] ^ data->h_source[5]) % count;
}