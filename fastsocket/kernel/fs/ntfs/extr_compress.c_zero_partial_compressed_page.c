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
typedef  int /*<<< orphan*/  u8 ;
struct page {scalar_t__ index; } ;
typedef  unsigned int const s64 ;

/* Variables and functions */
 unsigned int const PAGE_CACHE_MASK ; 
 unsigned int const PAGE_CACHE_SHIFT ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  clear_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 

__attribute__((used)) static void zero_partial_compressed_page(struct page *page,
		const s64 initialized_size)
{
	u8 *kp = page_address(page);
	unsigned int kp_ofs;

	ntfs_debug("Zeroing page region outside initialized size.");
	if (((s64)page->index << PAGE_CACHE_SHIFT) >= initialized_size) {
		/*
		 * FIXME: Using clear_page() will become wrong when we get
		 * PAGE_CACHE_SIZE != PAGE_SIZE but for now there is no problem.
		 */
		clear_page(kp);
		return;
	}
	kp_ofs = initialized_size & ~PAGE_CACHE_MASK;
	memset(kp + kp_ofs, 0, PAGE_CACHE_SIZE - kp_ofs);
	return;
}