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
struct eth1394hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ skb_mac_header (struct sk_buff const*) ; 

__attribute__((used)) static inline struct eth1394hdr *eth1394_hdr(const struct sk_buff *skb)
{
	return (struct eth1394hdr *)skb_mac_header(skb);
}