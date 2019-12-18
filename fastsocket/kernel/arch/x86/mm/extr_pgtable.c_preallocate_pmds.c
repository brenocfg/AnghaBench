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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PGALLOC_GFP ; 
 int PREALLOCATED_PMDS ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pmds (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int preallocate_pmds(pmd_t *pmds[])
{
	int i;
	bool failed = false;

	for(i = 0; i < PREALLOCATED_PMDS; i++) {
		pmd_t *pmd = (pmd_t *)__get_free_page(PGALLOC_GFP);
		if (pmd == NULL)
			failed = true;
		pmds[i] = pmd;
	}

	if (failed) {
		free_pmds(pmds);
		return -ENOMEM;
	}

	return 0;
}