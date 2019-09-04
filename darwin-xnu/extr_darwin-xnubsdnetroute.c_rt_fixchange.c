#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct rtfc_arg {struct radix_node_head* rnh; struct rtentry* rt0; } ;
struct rtentry {int rt_flags; struct rtentry* rt_parent; } ;
struct radix_node_head {TYPE_1__* rnh_treetop; } ;
struct radix_node {int dummy; } ;
struct TYPE_8__ {int sa_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  sa_len; } ;
struct TYPE_6__ {int rn_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int RTF_CLONING ; 
 int RTF_PRCLONING ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int imin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 TYPE_2__* rt_key (struct rtentry*) ; 
 TYPE_3__* rt_mask (struct rtentry*) ; 
 int rtrequest_locked (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rt_fixchange(struct radix_node *rn, void *vp)
{
	struct rtentry *rt = (struct rtentry *)rn;
	struct rtfc_arg *ap = vp;
	struct rtentry *rt0 = ap->rt0;
	struct radix_node_head *rnh = ap->rnh;
	u_char *xk1, *xm1, *xk2, *xmp;
	int i, len;

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);

	RT_LOCK(rt);

	if (!rt->rt_parent ||
	    (rt->rt_flags & (RTF_CLONING | RTF_PRCLONING))) {
		RT_UNLOCK(rt);
		return (0);
	}

	if (rt->rt_parent == rt0)
		goto delete_rt;

	/*
	 * There probably is a function somewhere which does this...
	 * if not, there should be.
	 */
	len = imin(rt_key(rt0)->sa_len, rt_key(rt)->sa_len);

	xk1 = (u_char *)rt_key(rt0);
	xm1 = (u_char *)rt_mask(rt0);
	xk2 = (u_char *)rt_key(rt);

	/*
	 * Avoid applying a less specific route; do this only if the parent
	 * route (rt->rt_parent) is a network route, since otherwise its mask
	 * will be NULL if it is a cloning host route.
	 */
	if ((xmp = (u_char *)rt_mask(rt->rt_parent)) != NULL) {
		int mlen = rt_mask(rt->rt_parent)->sa_len;
		if (mlen > rt_mask(rt0)->sa_len) {
			RT_UNLOCK(rt);
			return (0);
		}

		for (i = rnh->rnh_treetop->rn_offset; i < mlen; i++) {
			if ((xmp[i] & ~(xmp[i] ^ xm1[i])) != xmp[i]) {
				RT_UNLOCK(rt);
				return (0);
			}
		}
	}

	for (i = rnh->rnh_treetop->rn_offset; i < len; i++) {
		if ((xk2[i] & xm1[i]) != xk1[i]) {
			RT_UNLOCK(rt);
			return (0);
		}
	}

	/*
	 * OK, this node is a clone, and matches the node currently being
	 * changed/added under the node's mask.  So, get rid of it.
	 */
delete_rt:
	/*
	 * Safe to drop rt_lock and use rt_key, since holding rnh_lock here
	 * prevents another thread from calling rt_setgate() on this route.
	 */
	RT_UNLOCK(rt);
	return (rtrequest_locked(RTM_DELETE, rt_key(rt), NULL,
	    rt_mask(rt), rt->rt_flags, NULL));
}