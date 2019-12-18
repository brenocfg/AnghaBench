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
struct tcphdr {int ece; int cwr; } ;
struct sk_buff {int dummy; } ;
struct ipt_ecn_info {int operation; int invert; } ;
typedef  int /*<<< orphan*/  _tcph ;

/* Variables and functions */
 int IPT_ECN_OP_MATCH_CWR ; 
 int IPT_ECN_OP_MATCH_ECE ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff const*) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct tcphdr*) ; 

__attribute__((used)) static inline bool match_tcp(const struct sk_buff *skb,
			     const struct ipt_ecn_info *einfo,
			     bool *hotdrop)
{
	struct tcphdr _tcph;
	const struct tcphdr *th;

	/* In practice, TCP match does this, so can't fail.  But let's
	 * be good citizens.
	 */
	th = skb_header_pointer(skb, ip_hdrlen(skb), sizeof(_tcph), &_tcph);
	if (th == NULL) {
		*hotdrop = false;
		return false;
	}

	if (einfo->operation & IPT_ECN_OP_MATCH_ECE) {
		if (einfo->invert & IPT_ECN_OP_MATCH_ECE) {
			if (th->ece == 1)
				return false;
		} else {
			if (th->ece == 0)
				return false;
		}
	}

	if (einfo->operation & IPT_ECN_OP_MATCH_CWR) {
		if (einfo->invert & IPT_ECN_OP_MATCH_CWR) {
			if (th->cwr == 1)
				return false;
		} else {
			if (th->cwr == 0)
				return false;
		}
	}

	return true;
}