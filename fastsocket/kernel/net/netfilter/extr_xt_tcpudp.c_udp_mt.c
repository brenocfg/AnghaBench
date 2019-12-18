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
struct xt_udp {int invflags; int /*<<< orphan*/ * dpts; int /*<<< orphan*/ * spts; } ;
struct xt_match_param {scalar_t__ fragoff; int* hotdrop; int /*<<< orphan*/  thoff; struct xt_udp* matchinfo; } ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  _udph ;

/* Variables and functions */
 int XT_UDP_INV_DSTPT ; 
 int XT_UDP_INV_SRCPT ; 
 int /*<<< orphan*/  duprintf (char*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ port_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct udphdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct udphdr*) ; 

__attribute__((used)) static bool udp_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct udphdr *uh;
	struct udphdr _udph;
	const struct xt_udp *udpinfo = par->matchinfo;

	/* Must not be a fragment. */
	if (par->fragoff != 0)
		return false;

	uh = skb_header_pointer(skb, par->thoff, sizeof(_udph), &_udph);
	if (uh == NULL) {
		/* We've been asked to examine this packet, and we
		   can't.  Hence, no choice but to drop. */
		duprintf("Dropping evil UDP tinygram.\n");
		*par->hotdrop = true;
		return false;
	}

	return port_match(udpinfo->spts[0], udpinfo->spts[1],
			  ntohs(uh->source),
			  !!(udpinfo->invflags & XT_UDP_INV_SRCPT))
		&& port_match(udpinfo->dpts[0], udpinfo->dpts[1],
			      ntohs(uh->dest),
			      !!(udpinfo->invflags & XT_UDP_INV_DSTPT));
}