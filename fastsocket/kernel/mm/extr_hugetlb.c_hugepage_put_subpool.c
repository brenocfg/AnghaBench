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
struct hugepage_subpool {int /*<<< orphan*/  count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_or_release_subpool (struct hugepage_subpool*) ; 

void hugepage_put_subpool(struct hugepage_subpool *spool)
{
	spin_lock(&spool->lock);
	BUG_ON(!spool->count);
	spool->count--;
	unlock_or_release_subpool(spool);
}