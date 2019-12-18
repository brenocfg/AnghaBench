#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfrm_state {TYPE_2__* type; } ;
struct sk_buff {TYPE_1__* sp; } ;
struct flowi {int dummy; } ;
struct TYPE_4__ {int (* reject ) (struct xfrm_state*,struct sk_buff*,struct flowi*) ;} ;
struct TYPE_3__ {int len; struct xfrm_state** xvec; } ;

/* Variables and functions */
 int stub1 (struct xfrm_state*,struct sk_buff*,struct flowi*) ; 

__attribute__((used)) static inline int
xfrm_secpath_reject(int idx, struct sk_buff *skb, struct flowi *fl)
{
	struct xfrm_state *x;

	if (!skb->sp || idx < 0 || idx >= skb->sp->len)
		return 0;
	x = skb->sp->xvec[idx];
	if (!x->type->reject)
		return 0;
	return x->type->reject(x, skb, fl);
}