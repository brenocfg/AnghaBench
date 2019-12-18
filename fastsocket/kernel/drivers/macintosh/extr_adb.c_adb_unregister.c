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
struct TYPE_2__ {int /*<<< orphan*/ * handler; scalar_t__ busy; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* adb_handler ; 
 int /*<<< orphan*/  adb_handler_lock ; 
 int /*<<< orphan*/  adb_handler_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yield () ; 

int
adb_unregister(int index)
{
	int ret = -ENODEV;

	mutex_lock(&adb_handler_mutex);
	write_lock_irq(&adb_handler_lock);
	if (adb_handler[index].handler) {
		while(adb_handler[index].busy) {
			write_unlock_irq(&adb_handler_lock);
			yield();
			write_lock_irq(&adb_handler_lock);
		}
		ret = 0;
		adb_handler[index].handler = NULL;
	}
	write_unlock_irq(&adb_handler_lock);
	mutex_unlock(&adb_handler_mutex);
	return ret;
}