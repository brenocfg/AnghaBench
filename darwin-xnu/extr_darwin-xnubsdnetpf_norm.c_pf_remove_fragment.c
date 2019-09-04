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
struct pf_fragment {int dummy; } ;

/* Variables and functions */
 scalar_t__ BUFFER_FRAGMENTS (struct pf_fragment*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_fragment*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_fragment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_next ; 
 int /*<<< orphan*/  pf_cache_pl ; 
 int /*<<< orphan*/  pf_cache_tree ; 
 int /*<<< orphan*/  pf_cachequeue ; 
 int /*<<< orphan*/  pf_frag_pl ; 
 int /*<<< orphan*/  pf_frag_tree ; 
 int /*<<< orphan*/  pf_fragqueue ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,struct pf_fragment*) ; 

__attribute__((used)) static void
pf_remove_fragment(struct pf_fragment *frag)
{
	if (BUFFER_FRAGMENTS(frag)) {
		RB_REMOVE(pf_frag_tree, &pf_frag_tree, frag);
		TAILQ_REMOVE(&pf_fragqueue, frag, frag_next);
		pool_put(&pf_frag_pl, frag);
	} else {
		RB_REMOVE(pf_frag_tree, &pf_cache_tree, frag);
		TAILQ_REMOVE(&pf_cachequeue, frag, frag_next);
		pool_put(&pf_cache_pl, frag);
	}
}