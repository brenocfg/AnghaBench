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
struct ip_vs_protocol {int dummy; } ;
struct ip_vs_conn {int dummy; } ;

/* Variables and functions */
 int NF_ACCEPT ; 

int
ip_vs_null_xmit(struct sk_buff *skb, struct ip_vs_conn *cp,
		struct ip_vs_protocol *pp)
{
	/* we do not touch skb and do not need pskb ptr */
	return NF_ACCEPT;
}