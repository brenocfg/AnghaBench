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
struct svc_cacherep {int /*<<< orphan*/  c_hash; int /*<<< orphan*/  c_lru; int /*<<< orphan*/  c_type; int /*<<< orphan*/  c_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC_NOCACHE ; 
 int /*<<< orphan*/  RC_UNUSED ; 
 int /*<<< orphan*/  drc_slab ; 
 struct svc_cacherep* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct svc_cacherep *
nfsd_reply_cache_alloc(void)
{
	struct svc_cacherep	*rp;

	rp = kmem_cache_alloc(drc_slab, GFP_KERNEL);
	if (rp) {
		rp->c_state = RC_UNUSED;
		rp->c_type = RC_NOCACHE;
		INIT_LIST_HEAD(&rp->c_lru);
		INIT_HLIST_NODE(&rp->c_hash);
	}
	return rp;
}