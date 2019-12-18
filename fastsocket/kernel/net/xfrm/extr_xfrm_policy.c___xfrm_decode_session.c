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
struct xfrm_policy_afinfo {int /*<<< orphan*/  (* decode_session ) (struct sk_buff*,struct flowi*,int) ;} ;
struct sk_buff {int dummy; } ;
struct flowi {int /*<<< orphan*/  secid; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int security_xfrm_decode_session (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct flowi*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_policy_afinfo* xfrm_policy_get_afinfo (unsigned int) ; 
 int /*<<< orphan*/  xfrm_policy_put_afinfo (struct xfrm_policy_afinfo*) ; 

int __xfrm_decode_session(struct sk_buff *skb, struct flowi *fl,
			  unsigned int family, int reverse)
{
	struct xfrm_policy_afinfo *afinfo = xfrm_policy_get_afinfo(family);
	int err;

	if (unlikely(afinfo == NULL))
		return -EAFNOSUPPORT;

	afinfo->decode_session(skb, fl, reverse);
	err = security_xfrm_decode_session(skb, &fl->secid);
	xfrm_policy_put_afinfo(afinfo);
	return err;
}