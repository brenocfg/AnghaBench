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
typedef  scalar_t__ u32 ;
struct xfrm_state {struct xfrm_sec_ctx* security; } ;
struct xfrm_sec_ctx {scalar_t__ ctx_sid; } ;
struct sk_buff {struct sec_path* sp; } ;
struct sec_path {int len; struct xfrm_state** xvec; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SECSID_NULL ; 
 scalar_t__ selinux_authorizable_xfrm (struct xfrm_state*) ; 

__attribute__((used)) static int selinux_xfrm_skb_sid_ingress(struct sk_buff *skb,
					u32 *sid, int ckall)
{
	struct sec_path *sp = skb->sp;

	*sid = SECSID_NULL;

	if (sp) {
		int i, sid_set = 0;

		for (i = sp->len-1; i >= 0; i--) {
			struct xfrm_state *x = sp->xvec[i];
			if (selinux_authorizable_xfrm(x)) {
				struct xfrm_sec_ctx *ctx = x->security;

				if (!sid_set) {
					*sid = ctx->ctx_sid;
					sid_set = 1;

					if (!ckall)
						break;
				} else if (*sid != ctx->ctx_sid)
					return -EINVAL;
			}
		}
	}

	return 0;
}