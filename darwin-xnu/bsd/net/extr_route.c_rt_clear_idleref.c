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
struct rtentry {int rt_flags; int /*<<< orphan*/  (* rt_if_ref_fn ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  rt_ifp; } ;

/* Variables and functions */
 int RTF_IFREF ; 
 int RTF_NOIFREF ; 
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

void
rt_clear_idleref(struct rtentry *rt)
{
	RT_LOCK_ASSERT_HELD(rt);

	if (rt->rt_if_ref_fn != NULL) {
		VERIFY((rt->rt_flags & (RTF_NOIFREF | RTF_IFREF)) == RTF_IFREF);
		/* Become a regular mutex, just in case */
		RT_CONVERT_LOCK(rt);
		rt->rt_if_ref_fn(rt->rt_ifp, -1);
		rt->rt_flags &= ~RTF_IFREF;
		rt->rt_if_ref_fn = NULL;
	}
}