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
struct io_context {int /*<<< orphan*/  lock; int /*<<< orphan*/ * aic; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_as_io_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void as_trim(struct io_context *ioc)
{
	spin_lock_irq(&ioc->lock);
	if (ioc->aic)
		free_as_io_context(ioc->aic);
	ioc->aic = NULL;
	spin_unlock_irq(&ioc->lock);
}