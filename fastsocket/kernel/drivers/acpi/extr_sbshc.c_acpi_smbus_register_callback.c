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
struct acpi_smb_hc {int /*<<< orphan*/  lock; void* context; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  smbus_alarm_callback ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int acpi_smbus_register_callback(struct acpi_smb_hc *hc,
			         smbus_alarm_callback callback, void *context)
{
	mutex_lock(&hc->lock);
	hc->callback = callback;
	hc->context = context;
	mutex_unlock(&hc->lock);
	return 0;
}