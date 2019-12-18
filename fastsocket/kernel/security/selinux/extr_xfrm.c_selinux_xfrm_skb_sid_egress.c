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
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state {TYPE_1__* security; } ;
struct sk_buff {int dummy; } ;
struct dst_entry {struct xfrm_state* xfrm; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx_sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECSID_NULL ; 
 int /*<<< orphan*/  selinux_authorizable_xfrm (struct xfrm_state*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static u32 selinux_xfrm_skb_sid_egress(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct xfrm_state *x;

	if (dst == NULL)
		return SECSID_NULL;
	x = dst->xfrm;
	if (x == NULL || !selinux_authorizable_xfrm(x))
		return SECSID_NULL;

	return x->security->ctx_sid;
}