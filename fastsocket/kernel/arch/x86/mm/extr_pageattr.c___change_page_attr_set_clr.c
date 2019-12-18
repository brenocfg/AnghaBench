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
struct cpa_data {int numpages; int flags; int* vaddr; int /*<<< orphan*/  curpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CPA_ARRAY ; 
 int CPA_PAGES_ARRAY ; 
 int PAGE_SIZE ; 
 int __change_page_attr (struct cpa_data*,int) ; 
 int /*<<< orphan*/  cpa_lock ; 
 int cpa_process_alias (struct cpa_data*) ; 
 int /*<<< orphan*/  debug_pagealloc ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __change_page_attr_set_clr(struct cpa_data *cpa, int checkalias)
{
	int ret, numpages = cpa->numpages;

	while (numpages) {
		/*
		 * Store the remaining nr of pages for the large page
		 * preservation check.
		 */
		cpa->numpages = numpages;
		/* for array changes, we can't use large page */
		if (cpa->flags & (CPA_ARRAY | CPA_PAGES_ARRAY))
			cpa->numpages = 1;

		if (!debug_pagealloc)
			spin_lock(&cpa_lock);
		ret = __change_page_attr(cpa, checkalias);
		if (!debug_pagealloc)
			spin_unlock(&cpa_lock);
		if (ret)
			return ret;

		if (checkalias) {
			ret = cpa_process_alias(cpa);
			if (ret)
				return ret;
		}

		/*
		 * Adjust the number of pages with the result of the
		 * CPA operation. Either a large page has been
		 * preserved or a single page update happened.
		 */
		BUG_ON(cpa->numpages > numpages);
		numpages -= cpa->numpages;
		if (cpa->flags & (CPA_PAGES_ARRAY | CPA_ARRAY))
			cpa->curpage++;
		else
			*cpa->vaddr += cpa->numpages * PAGE_SIZE;

	}
	return 0;
}