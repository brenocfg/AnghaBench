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
struct xt_match_param {scalar_t__ fragoff; int* hotdrop; int /*<<< orphan*/  thoff; struct ipt_icmp* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct ipt_icmp {int invflags; int /*<<< orphan*/ * code; int /*<<< orphan*/  type; } ;
struct icmphdr {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  _icmph ;

/* Variables and functions */
 int IPT_ICMP_INV ; 
 int /*<<< orphan*/  duprintf (char*) ; 
 int icmp_type_code_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct icmphdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct icmphdr*) ; 

__attribute__((used)) static bool
icmp_match(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct icmphdr *ic;
	struct icmphdr _icmph;
	const struct ipt_icmp *icmpinfo = par->matchinfo;

	/* Must not be a fragment. */
	if (par->fragoff != 0)
		return false;

	ic = skb_header_pointer(skb, par->thoff, sizeof(_icmph), &_icmph);
	if (ic == NULL) {
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to drop.
		 */
		duprintf("Dropping evil ICMP tinygram.\n");
		*par->hotdrop = true;
		return false;
	}

	return icmp_type_code_match(icmpinfo->type,
				    icmpinfo->code[0],
				    icmpinfo->code[1],
				    ic->type, ic->code,
				    !!(icmpinfo->invflags&IPT_ICMP_INV));
}