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
struct ip_vs_iphdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  protocol; } ;
struct ip_vs_conn_param {int dummy; } ;
typedef  int /*<<< orphan*/  _ports ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_conn_fill_param (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ip_vs_conn_param*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff const*,unsigned int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ip_vs_conn_fill_param_proto(int af, const struct sk_buff *skb,
			    const struct ip_vs_iphdr *iph,
			    unsigned int proto_off, int inverse,
			    struct ip_vs_conn_param *p)
{
	__be16 _ports[2], *pptr;

	pptr = skb_header_pointer(skb, proto_off, sizeof(_ports), _ports);
	if (pptr == NULL)
		return 1;

	if (likely(!inverse))
		ip_vs_conn_fill_param(af, iph->protocol, &iph->saddr, pptr[0],
				      &iph->daddr, pptr[1], p);
	else
		ip_vs_conn_fill_param(af, iph->protocol, &iph->daddr, pptr[1],
				      &iph->saddr, pptr[0], p);
	return 0;
}