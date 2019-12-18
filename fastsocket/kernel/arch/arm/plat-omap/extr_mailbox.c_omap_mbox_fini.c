#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap_mbox {TYPE_1__* ops; int /*<<< orphan*/  irq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct omap_mbox*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct omap_mbox*) ; 
 int /*<<< orphan*/  mbox_queue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_mbox*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/  (*) (struct omap_mbox*)) ; 

__attribute__((used)) static void omap_mbox_fini(struct omap_mbox *mbox)
{
	mbox_queue_free(mbox->txq);
	mbox_queue_free(mbox->rxq);

	free_irq(mbox->irq, mbox);

	if (unlikely(mbox->ops->shutdown))
		mbox->ops->shutdown(mbox);
}