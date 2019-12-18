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
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {int h_proto; } ;

/* Variables and functions */
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 

__attribute__((used)) static inline int qeth_get_ip_version(struct sk_buff *skb)
{
	struct ethhdr *ehdr = (struct ethhdr *)skb->data;
	switch (ehdr->h_proto) {
	case ETH_P_IPV6:
		return 6;
	case ETH_P_IP:
		return 4;
	default:
		return 0;
	}
}