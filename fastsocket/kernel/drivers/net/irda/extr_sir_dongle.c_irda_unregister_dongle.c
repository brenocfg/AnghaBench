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
struct dongle_driver {int /*<<< orphan*/  dongle_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dongle_list_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int irda_unregister_dongle(struct dongle_driver *drv)
{
	mutex_lock(&dongle_list_lock);
	list_del(&drv->dongle_list);
	mutex_unlock(&dongle_list_lock);
	return 0;
}