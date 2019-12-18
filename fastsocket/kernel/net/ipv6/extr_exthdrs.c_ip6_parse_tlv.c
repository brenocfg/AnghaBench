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
struct tlvtype_proc {unsigned char const type; int /*<<< orphan*/  (* func ) (struct sk_buff*,int) ;} ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
#define  IPV6_TLV_PAD0 129 
#define  IPV6_TLV_PADN 128 
 int /*<<< orphan*/  ip6_tlvopt_unknown (struct sk_buff*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 int* skb_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int) ; 

__attribute__((used)) static int ip6_parse_tlv(struct tlvtype_proc *procs, struct sk_buff *skb)
{
	struct tlvtype_proc *curr;
	const unsigned char *nh = skb_network_header(skb);
	int off = skb_network_header_len(skb);
	int len = (skb_transport_header(skb)[1] + 1) << 3;

	if (skb_transport_offset(skb) + len > skb_headlen(skb))
		goto bad;

	off += 2;
	len -= 2;

	while (len > 0) {
		int optlen = nh[off + 1] + 2;

		switch (nh[off]) {
		case IPV6_TLV_PAD0:
			optlen = 1;
			break;

		case IPV6_TLV_PADN:
			break;

		default: /* Other TLV code so scan list */
			if (optlen > len)
				goto bad;
			for (curr=procs; curr->type >= 0; curr++) {
				if (curr->type == nh[off]) {
					/* type specific length/alignment
					   checks will be performed in the
					   func(). */
					if (curr->func(skb, off) == 0)
						return 0;
					break;
				}
			}
			if (curr->type < 0) {
				if (ip6_tlvopt_unknown(skb, off) == 0)
					return 0;
			}
			break;
		}
		off += optlen;
		len -= optlen;
	}
	if (len == 0)
		return 1;
bad:
	kfree_skb(skb);
	return 0;
}