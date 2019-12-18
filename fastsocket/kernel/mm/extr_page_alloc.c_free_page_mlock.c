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

/* Variables and functions */
 int /*<<< orphan*/  NR_MLOCK ; 
 int /*<<< orphan*/  UNEVICTABLE_MLOCKFREED ; 
 int /*<<< orphan*/  __count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void free_page_mlock(struct page *page)
{
	__dec_zone_page_state(page, NR_MLOCK);
	__count_vm_event(UNEVICTABLE_MLOCKFREED);
}