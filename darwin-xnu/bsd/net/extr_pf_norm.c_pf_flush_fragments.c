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
 int /*<<< orphan*/  DPFPRINTF (char*) ; 
 struct pf_fragment* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_cachequeue ; 
 int /*<<< orphan*/  pf_fragqueue ; 
 int /*<<< orphan*/  pf_free_fragment (struct pf_fragment*) ; 
 int pf_ncache ; 
 int pf_nfrents ; 

__attribute__((used)) static void
pf_flush_fragments(void)
{
	struct pf_fragment	*frag;
	int			 goal;

	goal = pf_nfrents * 9 / 10;
	DPFPRINTF(("trying to free > %d frents\n",
	    pf_nfrents - goal));
	while (goal < pf_nfrents) {
		frag = TAILQ_LAST(&pf_fragqueue, pf_fragqueue);
		if (frag == NULL)
			break;
		pf_free_fragment(frag);
	}


	goal = pf_ncache * 9 / 10;
	DPFPRINTF(("trying to free > %d cache entries\n",
	    pf_ncache - goal));
	while (goal < pf_ncache) {
		frag = TAILQ_LAST(&pf_cachequeue, pf_cachequeue);
		if (frag == NULL)
			break;
		pf_free_fragment(frag);
	}
}