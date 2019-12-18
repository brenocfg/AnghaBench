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
struct mtdoops_context {scalar_t__ writecount; int /*<<< orphan*/  work_write; int /*<<< orphan*/  writecount_lock; scalar_t__ ready; struct mtd_info* mtd; } ;
struct mtd_info {scalar_t__ panic_write; } ;

/* Variables and functions */
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  mtdoops_write (struct mtdoops_context*,int) ; 
 struct mtdoops_context oops_cxt ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mtdoops_console_sync(void)
{
	struct mtdoops_context *cxt = &oops_cxt;
	struct mtd_info *mtd = cxt->mtd;
	unsigned long flags;

	if (!cxt->ready || !mtd || cxt->writecount == 0)
		return;

	/* 
	 *  Once ready is 0 and we've held the lock no further writes to the 
	 *  buffer will happen
	 */
	spin_lock_irqsave(&cxt->writecount_lock, flags);
	if (!cxt->ready) {
		spin_unlock_irqrestore(&cxt->writecount_lock, flags);
		return;
	}
	cxt->ready = 0;
	spin_unlock_irqrestore(&cxt->writecount_lock, flags);

	if (mtd->panic_write && in_interrupt())
		/* Interrupt context, we're going to panic so try and log */
		mtdoops_write(cxt, 1);
	else
		schedule_work(&cxt->work_write);
}