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
struct page {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_locked ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int __wait_on_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_waitqueue (struct page*) ; 
 int /*<<< orphan*/  sync_page_killable ; 
 int /*<<< orphan*/  wait ; 

int __lock_page_killable(struct page *page)
{
	DEFINE_WAIT_BIT(wait, &page->flags, PG_locked);

	return __wait_on_bit_lock(page_waitqueue(page), &wait,
					sync_page_killable, TASK_KILLABLE);
}