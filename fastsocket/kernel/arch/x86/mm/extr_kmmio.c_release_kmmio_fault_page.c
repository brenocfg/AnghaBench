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
struct kmmio_fault_page {scalar_t__ count; struct kmmio_fault_page* release_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  disarm_kmmio_fault_page (struct kmmio_fault_page*) ; 
 struct kmmio_fault_page* get_kmmio_fault_page (unsigned long) ; 

__attribute__((used)) static void release_kmmio_fault_page(unsigned long page,
				struct kmmio_fault_page **release_list)
{
	struct kmmio_fault_page *f;

	page &= PAGE_MASK;
	f = get_kmmio_fault_page(page);
	if (!f)
		return;

	f->count--;
	BUG_ON(f->count < 0);
	if (!f->count) {
		disarm_kmmio_fault_page(f);
		f->release_next = *release_list;
		*release_list = f;
	}
}