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
struct as_io_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  as_ioc_count ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elv_ioc_count_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elv_ioc_count_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ioc_gone ; 
 int /*<<< orphan*/  ioc_gone_lock ; 
 int /*<<< orphan*/  kfree (struct as_io_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_as_io_context(struct as_io_context *aic)
{
	kfree(aic);
	elv_ioc_count_dec(as_ioc_count);
	if (ioc_gone) {
		/*
		 * AS scheduler is exiting, grab exit lock and check
		 * the pending io context count. If it hits zero,
		 * complete ioc_gone and set it back to NULL.
		 */
		spin_lock(&ioc_gone_lock);
		if (ioc_gone && !elv_ioc_count_read(as_ioc_count)) {
			complete(ioc_gone);
			ioc_gone = NULL;
		}
		spin_unlock(&ioc_gone_lock);
	}
}