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
struct TYPE_2__ {int /*<<< orphan*/  ipmi_lock; } ;

/* Variables and functions */
 TYPE_1__ driver_data ; 
 int /*<<< orphan*/  ipmi_update_global_handler () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmi_probe_complete(void)
{
	mutex_lock(&driver_data.ipmi_lock);
	ipmi_update_global_handler();
	mutex_unlock(&driver_data.ipmi_lock);
}