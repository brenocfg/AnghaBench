#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct iphdr {scalar_t__ protocol; int ihl; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  gateway; } ;
struct TYPE_6__ {int code; TYPE_1__ un; } ;
struct TYPE_5__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
#define  ICMP_REDIR_HOST 131 
#define  ICMP_REDIR_HOSTTOS 130 
#define  ICMP_REDIR_NET 129 
#define  ICMP_REDIR_NETTOS 128 
 scalar_t__ IPPROTO_ICMP ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 TYPE_3__* icmp_hdr (struct sk_buff*) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_rt_redirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ping_err (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void icmp_redirect(struct sk_buff *skb)
{
	struct iphdr *iph;

	if (skb->len < sizeof(struct iphdr))
		goto out_err;

	/*
	 *	Get the copied header of the packet that caused the redirect
	 */
	if (!pskb_may_pull(skb, sizeof(struct iphdr)))
		goto out;

	iph = (struct iphdr *)skb->data;

	switch (icmp_hdr(skb)->code & 7) {
	case ICMP_REDIR_NET:
	case ICMP_REDIR_NETTOS:
		/*
		 * As per RFC recommendations now handle it as a host redirect.
		 */
	case ICMP_REDIR_HOST:
	case ICMP_REDIR_HOSTTOS:
		ip_rt_redirect(ip_hdr(skb)->saddr, iph->daddr,
			       icmp_hdr(skb)->un.gateway,
			       iph->saddr, skb->dev);
		break;
	}

	/* Ping wants to see redirects.
         * Let's pretend they are errors of sorts... */
	if (iph->protocol == IPPROTO_ICMP &&
	    iph->ihl >= 5 &&
	    pskb_may_pull(skb, (iph->ihl<<2)+8)) {
		ping_err(skb, icmp_hdr(skb)->un.gateway);
	}

out:
	return;
out_err:
	ICMP_INC_STATS_BH(dev_net(skb->dev), ICMP_MIB_INERRORS);
	goto out;
}