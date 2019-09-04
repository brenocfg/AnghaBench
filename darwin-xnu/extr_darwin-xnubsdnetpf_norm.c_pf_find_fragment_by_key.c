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
struct pf_fragment {int /*<<< orphan*/  fr_timeout; } ;
struct pf_frag_tree {int dummy; } ;

/* Variables and functions */
 scalar_t__ BUFFER_FRAGMENTS (struct pf_fragment*) ; 
 struct pf_fragment* RB_FIND (int /*<<< orphan*/ ,struct pf_frag_tree*,struct pf_fragment*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pf_fragment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_fragment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_next ; 
 int /*<<< orphan*/  pf_cachequeue ; 
 int /*<<< orphan*/  pf_frag_tree ; 
 int /*<<< orphan*/  pf_fragqueue ; 
 int /*<<< orphan*/  pf_time_second () ; 

__attribute__((used)) static struct pf_fragment *
pf_find_fragment_by_key(struct pf_fragment *key, struct pf_frag_tree *tree)
{
	struct pf_fragment *frag;
	
	frag = RB_FIND(pf_frag_tree, tree, key);
	if (frag != NULL) {
		/* XXX Are we sure we want to update the timeout? */
		frag->fr_timeout = pf_time_second();
		if (BUFFER_FRAGMENTS(frag)) {
			TAILQ_REMOVE(&pf_fragqueue, frag, frag_next);
			TAILQ_INSERT_HEAD(&pf_fragqueue, frag, frag_next);
		} else {
			TAILQ_REMOVE(&pf_cachequeue, frag, frag_next);
			TAILQ_INSERT_HEAD(&pf_cachequeue, frag, frag_next);
		}
	}
	
	return (frag);
}