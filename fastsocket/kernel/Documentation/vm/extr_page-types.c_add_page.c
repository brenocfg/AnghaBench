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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  bit_mask_ok (int /*<<< orphan*/ ) ; 
 size_t hash_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwpoison_page (unsigned long) ; 
 int /*<<< orphan*/  kpageflags_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nr_pages ; 
 scalar_t__ opt_hwpoison ; 
 int opt_list ; 
 scalar_t__ opt_unpoison ; 
 int /*<<< orphan*/  show_page (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_page_range (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_pages ; 
 int /*<<< orphan*/  unpoison_page (unsigned long) ; 

__attribute__((used)) static void add_page(unsigned long voffset,
		     unsigned long offset, uint64_t flags)
{
	flags = kpageflags_flags(flags);

	if (!bit_mask_ok(flags))
		return;

	if (opt_hwpoison)
		hwpoison_page(offset);
	if (opt_unpoison)
		unpoison_page(offset);

	if (opt_list == 1)
		show_page_range(voffset, offset, flags);
	else if (opt_list == 2)
		show_page(voffset, offset, flags);

	nr_pages[hash_slot(flags)]++;
	total_pages++;
}