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
typedef  int u32 ;
typedef  int u16 ;
struct vxgedev {int no_of_vpath; int* vpath_selector; } ;
struct tcphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sk_buff {int protocol; } ;
struct iphdr {int frag_off; int ihl; scalar_t__ protocol; } ;

/* Variables and functions */
 int ETH_P_IP ; 
 scalar_t__ IPPROTO_UDP ; 
 int IP_MF ; 
 int IP_OFFSET ; 
 int htons (int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vxge_get_vpath_no(struct vxgedev *vdev, struct sk_buff *skb,
	int *do_lock)
{
	u16 queue_len, counter = 0;
	if (skb->protocol == htons(ETH_P_IP)) {
		struct iphdr *ip;
		struct tcphdr *th;

		ip = ip_hdr(skb);

		if ((ip->frag_off & htons(IP_OFFSET|IP_MF)) == 0) {
			th = (struct tcphdr *)(((unsigned char *)ip) +
					ip->ihl*4);

			queue_len = vdev->no_of_vpath;
			counter = (ntohs(th->source) +
				ntohs(th->dest)) &
				vdev->vpath_selector[queue_len - 1];
			if (counter >= queue_len)
				counter = queue_len - 1;

			if (ip->protocol == IPPROTO_UDP) {
#ifdef NETIF_F_LLTX
				*do_lock = 0;
#endif
			}
		}
	}
	return counter;
}