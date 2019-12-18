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
struct ipath_devdata {int /*<<< orphan*/  ipath_sdma_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_sdma_make_progress (struct ipath_devdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipath_sdma_intr(struct ipath_devdata *dd)
{
	unsigned long flags;

	spin_lock_irqsave(&dd->ipath_sdma_lock, flags);

	(void) ipath_sdma_make_progress(dd);

	spin_unlock_irqrestore(&dd->ipath_sdma_lock, flags);
}