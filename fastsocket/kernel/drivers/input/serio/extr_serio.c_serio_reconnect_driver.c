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
struct serio {int /*<<< orphan*/  drv_mutex; TYPE_1__* drv; } ;
struct TYPE_2__ {int (* reconnect ) (struct serio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct serio*) ; 

__attribute__((used)) static int serio_reconnect_driver(struct serio *serio)
{
	int retval = -1;

	mutex_lock(&serio->drv_mutex);
	if (serio->drv && serio->drv->reconnect)
		retval = serio->drv->reconnect(serio);
	mutex_unlock(&serio->drv_mutex);

	return retval;
}