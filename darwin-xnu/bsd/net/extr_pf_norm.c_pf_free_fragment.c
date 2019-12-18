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
struct pf_frent {scalar_t__ fr_off; scalar_t__ fr_end; int /*<<< orphan*/  fr_m; } ;
struct pf_frcache {scalar_t__ fr_off; scalar_t__ fr_end; int /*<<< orphan*/  fr_m; } ;
struct pf_fragment {int /*<<< orphan*/  fr_cache; int /*<<< orphan*/  fr_queue; } ;

/* Variables and functions */
 scalar_t__ BUFFER_FRAGMENTS (struct pf_fragment*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct pf_frent* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct pf_frent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  fr_next ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_cent_pl ; 
 int /*<<< orphan*/  pf_frent_pl ; 
 int /*<<< orphan*/  pf_ncache ; 
 int /*<<< orphan*/  pf_nfrents ; 
 int /*<<< orphan*/  pf_remove_fragment (struct pf_fragment*) ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,struct pf_frent*) ; 

__attribute__((used)) static void
pf_free_fragment(struct pf_fragment *frag)
{
	struct pf_frent		*frent;
	struct pf_frcache	*frcache;

	/* Free all fragments */
	if (BUFFER_FRAGMENTS(frag)) {
		for (frent = LIST_FIRST(&frag->fr_queue); frent;
		    frent = LIST_FIRST(&frag->fr_queue)) {
			LIST_REMOVE(frent, fr_next);

			m_freem(frent->fr_m);
			pool_put(&pf_frent_pl, frent);
			pf_nfrents--;
		}
	} else {
		for (frcache = LIST_FIRST(&frag->fr_cache); frcache;
		    frcache = LIST_FIRST(&frag->fr_cache)) {
			LIST_REMOVE(frcache, fr_next);

			VERIFY(LIST_EMPTY(&frag->fr_cache) ||
			    LIST_FIRST(&frag->fr_cache)->fr_off >
			    frcache->fr_end);

			pool_put(&pf_cent_pl, frcache);
			pf_ncache--;
		}
	}

	pf_remove_fragment(frag);
}