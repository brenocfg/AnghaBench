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
struct dock_data {int /*<<< orphan*/  ds; int /*<<< orphan*/  event; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  dock_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dock_data*) ; 

__attribute__((used)) static void acpi_dock_deferred_cb(void *context)
{
	struct dock_data *data = (struct dock_data *)context;

	dock_notify(data->handle, data->event, data->ds);
	kfree(data);
}