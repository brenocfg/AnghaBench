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
struct page {int /*<<< orphan*/  debug_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_DEBUG_FLAG_POISON ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_page_poison(struct page *page)
{
	__clear_bit(PAGE_DEBUG_FLAG_POISON, &page->debug_flags);
}