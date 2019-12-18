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
typedef  int __u32 ;

/* Variables and functions */
 int htonl (int) ; 
 scalar_t__ ipv6_hdr (struct sk_buff const*) ; 

__attribute__((used)) static int sctp_v6_is_ce(const struct sk_buff *skb)
{
	return *((__u32 *)(ipv6_hdr(skb))) & htonl(1 << 20);
}