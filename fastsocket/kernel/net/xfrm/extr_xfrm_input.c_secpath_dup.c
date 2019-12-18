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
struct sec_path {int len; int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * xvec; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct sec_path* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sec_path*,struct sec_path*,int) ; 
 int /*<<< orphan*/  secpath_cachep ; 
 int /*<<< orphan*/  xfrm_state_hold (int /*<<< orphan*/ ) ; 

struct sec_path *secpath_dup(struct sec_path *src)
{
	struct sec_path *sp;

	sp = kmem_cache_alloc(secpath_cachep, GFP_ATOMIC);
	if (!sp)
		return NULL;

	sp->len = 0;
	if (src) {
		int i;

		memcpy(sp, src, sizeof(*sp));
		for (i = 0; i < sp->len; i++)
			xfrm_state_hold(sp->xvec[i]);
	}
	atomic_set(&sp->refcnt, 1);
	return sp;
}