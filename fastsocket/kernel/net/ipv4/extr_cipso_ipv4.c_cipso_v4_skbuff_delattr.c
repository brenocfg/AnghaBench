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
struct sk_buff {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_options {scalar_t__ cipso; int is_changed; } ;
struct TYPE_2__ {struct ip_options opt; } ;

/* Variables and functions */
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPOPT_NOOP ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned char) ; 
 int skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 

int cipso_v4_skbuff_delattr(struct sk_buff *skb)
{
	int ret_val;
	struct iphdr *iph;
	struct ip_options *opt = &IPCB(skb)->opt;
	unsigned char *cipso_ptr;

	if (opt->cipso == 0)
		return 0;

	/* since we are changing the packet we should make a copy */
	ret_val = skb_cow(skb, skb_headroom(skb));
	if (ret_val < 0)
		return ret_val;

	/* the easiest thing to do is just replace the cipso option with noop
	 * options since we don't change the size of the packet, although we
	 * still need to recalculate the checksum */

	iph = ip_hdr(skb);
	cipso_ptr = (unsigned char *)iph + opt->cipso;
	memset(cipso_ptr, IPOPT_NOOP, cipso_ptr[1]);
	opt->cipso = 0;
	opt->is_changed = 1;

	ip_send_check(iph);

	return 0;
}