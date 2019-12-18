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
struct page {int /*<<< orphan*/  lru; } ;
struct anon_vma {int dummy; } ;
typedef  struct page* (* new_page_t ) (struct page*,unsigned long,int**) ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int MIGRATE_SYNC ; 
 scalar_t__ PageAnon (struct page*) ; 
 int TTU_IGNORE_ACCESS ; 
 int TTU_IGNORE_MLOCK ; 
 int TTU_MIGRATION ; 
 int /*<<< orphan*/  drop_anon_vma (struct anon_vma*) ; 
 int /*<<< orphan*/  get_anon_vma (struct anon_vma*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int move_to_new_page (struct page*,struct page*,int,int) ; 
 struct anon_vma* page_lock_anon_vma (struct page*) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  page_unlock_anon_vma (struct anon_vma*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  remove_migration_ptes (struct page*,struct page*) ; 
 int /*<<< orphan*/  try_to_unmap (struct page*,int) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int unmap_and_move_huge_page(new_page_t get_new_page,
				unsigned long private, struct page *hpage,
				int force, bool offlining,
				enum migrate_mode mode)
{
	int rc = 0;
	int *result = NULL;
	struct page *new_hpage = get_new_page(hpage, private, &result);
	struct anon_vma *anon_vma = NULL;

	if (!new_hpage)
		return -ENOMEM;

	rc = -EAGAIN;

	if (!trylock_page(hpage)) {
		if (!force || mode != MIGRATE_SYNC)
			goto out;
		lock_page(hpage);
	}

	if (PageAnon(hpage)) {
		anon_vma = page_lock_anon_vma(hpage);
		if (anon_vma) {
			get_anon_vma(anon_vma);
			page_unlock_anon_vma(anon_vma);
		}
	}

	try_to_unmap(hpage, TTU_MIGRATION|TTU_IGNORE_MLOCK|TTU_IGNORE_ACCESS);

	if (!page_mapped(hpage))
		rc = move_to_new_page(new_hpage, hpage, 1, mode);

	if (rc)
		remove_migration_ptes(hpage, hpage);

	if (anon_vma)
		drop_anon_vma(anon_vma);
out:
	unlock_page(hpage);

	if (rc != -EAGAIN) {
		list_del(&hpage->lru);
		put_page(hpage);
	}

	put_page(new_hpage);

	if (result) {
		if (rc)
			*result = rc;
		else
			*result = page_to_nid(new_hpage);
	}
	return rc;
}