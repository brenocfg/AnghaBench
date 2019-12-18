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
struct page {int dummy; } ;
typedef  enum km_type { ____Placeholder_km_type } km_type ;

/* Variables and functions */
 struct page* kmap_atomic_to_page (void*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int) ; 
 int /*<<< orphan*/  kvm_release_page_dirty (struct page*) ; 

__attribute__((used)) static void nested_svm_unmap(void *addr, enum km_type idx)
{
	struct page *page;

	if (!addr)
		return;

	page = kmap_atomic_to_page(addr);

	kunmap_atomic(addr, idx);
	kvm_release_page_dirty(page);
}