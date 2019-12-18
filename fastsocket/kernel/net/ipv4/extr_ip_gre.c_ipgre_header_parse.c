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
struct sk_buff {int dummy; } ;
struct iphdr {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ skb_mac_header (struct sk_buff const*) ; 

__attribute__((used)) static int ipgre_header_parse(const struct sk_buff *skb, unsigned char *haddr)
{
	struct iphdr *iph = (struct iphdr *) skb_mac_header(skb);
	memcpy(haddr, &iph->saddr, 4);
	return 4;
}