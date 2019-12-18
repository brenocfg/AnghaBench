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
struct qt2160_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  QT2160_CYCLE_INTERVAL ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qt2160_schedule_read(struct qt2160_data *qt2160)
{
	spin_lock_irq(&qt2160->lock);
	schedule_delayed_work(&qt2160->dwork, QT2160_CYCLE_INTERVAL);
	spin_unlock_irq(&qt2160->lock);
}