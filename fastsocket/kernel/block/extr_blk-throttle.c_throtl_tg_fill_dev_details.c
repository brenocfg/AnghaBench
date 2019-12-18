#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dev; } ;
struct throtl_grp {TYPE_1__ blkg; } ;
struct throtl_data {TYPE_2__* queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __throtl_tg_fill_dev_details (struct throtl_data*,struct throtl_grp*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
throtl_tg_fill_dev_details(struct throtl_data *td, struct throtl_grp *tg)
{
	if (!tg || tg->blkg.dev)
		return;

	spin_lock_irq(td->queue->queue_lock);
	__throtl_tg_fill_dev_details(td, tg);
	spin_unlock_irq(td->queue->queue_lock);
}