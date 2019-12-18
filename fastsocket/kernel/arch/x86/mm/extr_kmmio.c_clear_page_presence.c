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
struct kmmio_fault_page {unsigned int page; int /*<<< orphan*/  old_presence; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
#define  PG_LEVEL_2M 129 
#define  PG_LEVEL_4K 128 
 int /*<<< orphan*/  __flush_tlb_one (unsigned int) ; 
 int /*<<< orphan*/  clear_pmd_presence (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_pte_presence (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_address (unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static int clear_page_presence(struct kmmio_fault_page *f, bool clear)
{
	unsigned int level;
	pte_t *pte = lookup_address(f->page, &level);

	if (!pte) {
		pr_err("kmmio: no pte for page 0x%08lx\n", f->page);
		return -1;
	}

	switch (level) {
	case PG_LEVEL_2M:
		clear_pmd_presence((pmd_t *)pte, clear, &f->old_presence);
		break;
	case PG_LEVEL_4K:
		clear_pte_presence(pte, clear, &f->old_presence);
		break;
	default:
		pr_err("kmmio: unexpected page level 0x%x.\n", level);
		return -1;
	}

	__flush_tlb_one(f->page);
	return 0;
}