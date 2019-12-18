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
struct xfrm_selector {int dummy; } ;
struct xfrm_dst {int /*<<< orphan*/  partner; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int xfrm_dst_alloc_copy (void**,struct xfrm_selector*,int) ; 

__attribute__((used)) static int inline
xfrm_dst_update_parent(struct dst_entry *dst, struct xfrm_selector *sel)
{
#ifdef CONFIG_XFRM_SUB_POLICY
	struct xfrm_dst *xdst = (struct xfrm_dst *)dst;
	return xfrm_dst_alloc_copy((void **)&(xdst->partner),
				   sel, sizeof(*sel));
#else
	return 0;
#endif
}