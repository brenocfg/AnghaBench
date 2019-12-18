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
struct hugepage_subpool {scalar_t__ used_hpages; scalar_t__ max_hpages; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hugepage_subpool_get_pages(struct hugepage_subpool *spool,
				      long delta)
{
	int ret = 0;

	if (!spool)
		return 0;

	spin_lock(&spool->lock);
	if ((spool->used_hpages + delta) <= spool->max_hpages) {
		spool->used_hpages += delta;
	} else {
		ret = -ENOMEM;
	}
	spin_unlock(&spool->lock);

	return ret;
}