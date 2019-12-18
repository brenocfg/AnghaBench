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
 int /*<<< orphan*/  ADD_STATS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmd_update ; 
 int /*<<< orphan*/  pmd_update_pinned ; 
 int /*<<< orphan*/  xen_page_pinned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_set_pmd_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void xen_set_pmd(pmd_t *ptr, pmd_t val)
{
	ADD_STATS(pmd_update, 1);

	/* If page is not pinned, we can just update the entry
	   directly */
	if (!xen_page_pinned(ptr)) {
		*ptr = val;
		return;
	}

	ADD_STATS(pmd_update_pinned, 1);

	xen_set_pmd_hyper(ptr, val);
}