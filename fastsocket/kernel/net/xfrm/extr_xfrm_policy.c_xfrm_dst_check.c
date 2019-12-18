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
typedef  int /*<<< orphan*/  u32 ;
struct dst_entry {scalar_t__ obsolete; } ;

/* Variables and functions */
 int /*<<< orphan*/  stale_bundle (struct dst_entry*) ; 

__attribute__((used)) static struct dst_entry *xfrm_dst_check(struct dst_entry *dst, u32 cookie)
{
	/* Code (such as __xfrm4_bundle_create()) sets dst->obsolete
	 * to "-1" to force all XFRM destinations to get validated by
	 * dst_ops->check on every use.  We do this because when a
	 * normal route referenced by an XFRM dst is obsoleted we do
	 * not go looking around for all parent referencing XFRM dsts
	 * so that we can invalidate them.  It is just too much work.
	 * Instead we make the checks here on every use.  For example:
	 *
	 *	XFRM dst A --> IPv4 dst X
	 *
	 * X is the "xdst->route" of A (X is also the "dst->path" of A
	 * in this example).  If X is marked obsolete, "A" will not
	 * notice.  That's what we are validating here via the
	 * stale_bundle() check.
	 *
	 * When a policy's bundle is pruned, we dst_free() the XFRM
	 * dst which causes it's ->obsolete field to be set to a
	 * positive non-zero integer.  If an XFRM dst has been pruned
	 * like this, we want to force a new route lookup.
	 */
	if (dst->obsolete < 0 && !stale_bundle(dst))
		return dst;

	return NULL;
}