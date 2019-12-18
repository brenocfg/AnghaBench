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
struct srcu_notifier_head {int /*<<< orphan*/ * head; int /*<<< orphan*/  srcu; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void srcu_init_notifier_head(struct srcu_notifier_head *nh)
{
	mutex_init(&nh->mutex);
	if (init_srcu_struct(&nh->srcu) < 0)
		BUG();
	nh->head = NULL;
}