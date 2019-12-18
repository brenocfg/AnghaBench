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
struct xt_target_param {struct ip6t_HL_info* targinfo; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct ipv6hdr {int hop_limit; } ;
struct ip6t_HL_info {int mode; int hop_limit; } ;

/* Variables and functions */
#define  IP6T_HL_DEC 130 
#define  IP6T_HL_INC 129 
#define  IP6T_HL_SET 128 
 unsigned int NF_DROP ; 
 unsigned int XT_CONTINUE ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
hl_tg6(struct sk_buff *skb, const struct xt_target_param *par)
{
	struct ipv6hdr *ip6h;
	const struct ip6t_HL_info *info = par->targinfo;
	int new_hl;

	if (!skb_make_writable(skb, skb->len))
		return NF_DROP;

	ip6h = ipv6_hdr(skb);

	switch (info->mode) {
		case IP6T_HL_SET:
			new_hl = info->hop_limit;
			break;
		case IP6T_HL_INC:
			new_hl = ip6h->hop_limit + info->hop_limit;
			if (new_hl > 255)
				new_hl = 255;
			break;
		case IP6T_HL_DEC:
			new_hl = ip6h->hop_limit - info->hop_limit;
			if (new_hl < 0)
				new_hl = 0;
			break;
		default:
			new_hl = ip6h->hop_limit;
			break;
	}

	ip6h->hop_limit = new_hl;

	return XT_CONTINUE;
}