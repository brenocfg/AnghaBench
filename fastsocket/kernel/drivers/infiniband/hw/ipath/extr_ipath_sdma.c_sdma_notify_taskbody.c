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
struct list_head {int dummy; } ;
struct ipath_devdata {int /*<<< orphan*/  verbs_dev; int /*<<< orphan*/  ipath_sdma_lock; int /*<<< orphan*/  ipath_sdma_notifylist; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  ipath_ib_piobufavail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_sdma_notify (struct ipath_devdata*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sdma_notify_taskbody(struct ipath_devdata *dd)
{
	unsigned long flags;
	struct list_head list;

	INIT_LIST_HEAD(&list);

	spin_lock_irqsave(&dd->ipath_sdma_lock, flags);

	list_splice_init(&dd->ipath_sdma_notifylist, &list);

	spin_unlock_irqrestore(&dd->ipath_sdma_lock, flags);

	ipath_sdma_notify(dd, &list);

	/*
	 * The IB verbs layer needs to see the callback before getting
	 * the call to ipath_ib_piobufavail() because the callback
	 * handles releasing resources the next send will need.
	 * Otherwise, we could do these calls in
	 * ipath_sdma_make_progress().
	 */
	ipath_ib_piobufavail(dd->verbs_dev);
}