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
typedef  int u64 ;
struct page {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KPF_ACTIVE ; 
 int KPF_ANON ; 
 int /*<<< orphan*/  KPF_ARCH ; 
 int /*<<< orphan*/  KPF_BUDDY ; 
 int KPF_COMPOUND_HEAD ; 
 int KPF_COMPOUND_TAIL ; 
 int /*<<< orphan*/  KPF_DIRTY ; 
 int /*<<< orphan*/  KPF_ERROR ; 
 int KPF_HUGE ; 
 int /*<<< orphan*/  KPF_HWPOISON ; 
 int KPF_KSM ; 
 int /*<<< orphan*/  KPF_LOCKED ; 
 int /*<<< orphan*/  KPF_LRU ; 
 int /*<<< orphan*/  KPF_MAPPEDTODISK ; 
 int /*<<< orphan*/  KPF_MLOCKED ; 
 int KPF_MMAP ; 
 int KPF_NOPAGE ; 
 int /*<<< orphan*/  KPF_OWNER_PRIVATE ; 
 int /*<<< orphan*/  KPF_PRIVATE ; 
 int /*<<< orphan*/  KPF_PRIVATE_2 ; 
 int /*<<< orphan*/  KPF_RECLAIM ; 
 int /*<<< orphan*/  KPF_REFERENCED ; 
 int /*<<< orphan*/  KPF_RESERVED ; 
 int /*<<< orphan*/  KPF_SLAB ; 
 int /*<<< orphan*/  KPF_SWAPBACKED ; 
 int /*<<< orphan*/  KPF_SWAPCACHE ; 
 int /*<<< orphan*/  KPF_UNCACHED ; 
 int /*<<< orphan*/  KPF_UNEVICTABLE ; 
 int /*<<< orphan*/  KPF_UPTODATE ; 
 int /*<<< orphan*/  KPF_WRITEBACK ; 
 int /*<<< orphan*/  PG_active ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int /*<<< orphan*/  PG_buddy ; 
 int /*<<< orphan*/  PG_dirty ; 
 int /*<<< orphan*/  PG_error ; 
 int /*<<< orphan*/  PG_hwpoison ; 
 int /*<<< orphan*/  PG_locked ; 
 int /*<<< orphan*/  PG_lru ; 
 int /*<<< orphan*/  PG_mappedtodisk ; 
 int /*<<< orphan*/  PG_mlocked ; 
 int /*<<< orphan*/  PG_owner_priv_1 ; 
 int /*<<< orphan*/  PG_private ; 
 int /*<<< orphan*/  PG_private_2 ; 
 int /*<<< orphan*/  PG_reclaim ; 
 int /*<<< orphan*/  PG_referenced ; 
 int /*<<< orphan*/  PG_reserved ; 
 int /*<<< orphan*/  PG_slab ; 
 int /*<<< orphan*/  PG_swapbacked ; 
 int /*<<< orphan*/  PG_swapcache ; 
 int /*<<< orphan*/  PG_uncached ; 
 int /*<<< orphan*/  PG_unevictable ; 
 int /*<<< orphan*/  PG_uptodate ; 
 int /*<<< orphan*/  PG_writeback ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageHead (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageKsm (struct page*) ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 scalar_t__ PageTail (struct page*) ; 
 int kpf_copy_bit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_mapped (struct page*) ; 

u64 stable_page_flags(struct page *page)
{
	u64 k;
	u64 u;

	/*
	 * pseudo flag: KPF_NOPAGE
	 * it differentiates a memory hole from a page with no flags
	 */
	if (!page)
		return 1 << KPF_NOPAGE;

	k = page->flags;
	u = 0;

	/*
	 * pseudo flags for the well known (anonymous) memory mapped pages
	 *
	 * Note that page->_mapcount is overloaded in SLOB/SLUB/SLQB, so the
	 * simple test in page_mapped() is not enough.
	 */
	if (!PageSlab(page) && page_mapped(page))
		u |= 1 << KPF_MMAP;
	if (PageAnon(page))
		u |= 1 << KPF_ANON;
	if (PageKsm(page))
		u |= 1 << KPF_KSM;

	/*
	 * compound pages: export both head/tail info
	 * they together define a compound page's start/end pos and order
	 */
	if (PageHead(page))
		u |= 1 << KPF_COMPOUND_HEAD;
	if (PageTail(page))
		u |= 1 << KPF_COMPOUND_TAIL;
	if (PageHuge(page))
		u |= 1 << KPF_HUGE;

	u |= kpf_copy_bit(k, KPF_LOCKED,	PG_locked);

	/*
	 * Caveats on high order pages:
	 * PG_buddy will only be set on the head page; SLUB/SLQB do the same
	 * for PG_slab; SLOB won't set PG_slab at all on compound pages.
	 */
	u |= kpf_copy_bit(k, KPF_SLAB,		PG_slab);
	u |= kpf_copy_bit(k, KPF_BUDDY,		PG_buddy);

	u |= kpf_copy_bit(k, KPF_ERROR,		PG_error);
	u |= kpf_copy_bit(k, KPF_DIRTY,		PG_dirty);
	u |= kpf_copy_bit(k, KPF_UPTODATE,	PG_uptodate);
	u |= kpf_copy_bit(k, KPF_WRITEBACK,	PG_writeback);

	u |= kpf_copy_bit(k, KPF_LRU,		PG_lru);
	u |= kpf_copy_bit(k, KPF_REFERENCED,	PG_referenced);
	u |= kpf_copy_bit(k, KPF_ACTIVE,	PG_active);
	u |= kpf_copy_bit(k, KPF_RECLAIM,	PG_reclaim);

	u |= kpf_copy_bit(k, KPF_SWAPCACHE,	PG_swapcache);
	u |= kpf_copy_bit(k, KPF_SWAPBACKED,	PG_swapbacked);

	u |= kpf_copy_bit(k, KPF_UNEVICTABLE,	PG_unevictable);
	u |= kpf_copy_bit(k, KPF_MLOCKED,	PG_mlocked);

#ifdef CONFIG_MEMORY_FAILURE
	u |= kpf_copy_bit(k, KPF_HWPOISON,	PG_hwpoison);
#endif

#ifdef CONFIG_IA64_UNCACHED_ALLOCATOR
	u |= kpf_copy_bit(k, KPF_UNCACHED,	PG_uncached);
#endif

	u |= kpf_copy_bit(k, KPF_RESERVED,	PG_reserved);
	u |= kpf_copy_bit(k, KPF_MAPPEDTODISK,	PG_mappedtodisk);
	u |= kpf_copy_bit(k, KPF_PRIVATE,	PG_private);
	u |= kpf_copy_bit(k, KPF_PRIVATE_2,	PG_private_2);
	u |= kpf_copy_bit(k, KPF_OWNER_PRIVATE,	PG_owner_priv_1);
	u |= kpf_copy_bit(k, KPF_ARCH,		PG_arch_1);

	return u;
}