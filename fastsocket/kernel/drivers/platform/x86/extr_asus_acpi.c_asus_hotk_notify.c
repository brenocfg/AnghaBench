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
typedef  int u32 ;
struct acpi_device {int dummy; } ;
struct TYPE_2__ {int brightness; int /*<<< orphan*/ * event_count; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ACPI_MAX_SYS_NOTIFY ; 
 scalar_t__ BR_DOWN ; 
 scalar_t__ BR_UP ; 
 int /*<<< orphan*/  acpi_bus_generate_proc_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* hotk ; 

__attribute__((used)) static void asus_hotk_notify(struct acpi_device *device, u32 event)
{
	/* TODO Find a better way to handle events count. */
	if (!hotk)
		return;

	/*
	 * The BIOS *should* be sending us device events, but apparently
	 * Asus uses system events instead, so just ignore any device
	 * events we get.
	 */
	if (event > ACPI_MAX_SYS_NOTIFY)
		return;

	if ((event & ~((u32) BR_UP)) < 16)
		hotk->brightness = (event & ~((u32) BR_UP));
	else if ((event & ~((u32) BR_DOWN)) < 16)
		hotk->brightness = (event & ~((u32) BR_DOWN));

	acpi_bus_generate_proc_event(hotk->device, event,
				hotk->event_count[event % 128]++);

	return;
}