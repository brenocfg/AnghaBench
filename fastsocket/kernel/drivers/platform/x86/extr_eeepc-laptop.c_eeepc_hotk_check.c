#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct acpi_buffer {int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {scalar_t__ present; } ;
struct TYPE_6__ {TYPE_1__ status; } ;
struct TYPE_5__ {int /*<<< orphan*/  cm_supported; int /*<<< orphan*/  handle; int /*<<< orphan*/  init_flag; TYPE_3__* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int EINVAL ; 
 int ENODEV ; 
 int acpi_bus_get_status (TYPE_3__*) ; 
 int /*<<< orphan*/  cmsg_quirks () ; 
 TYPE_2__* ehotk ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_acpi_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct acpi_buffer*) ; 

__attribute__((used)) static int eeepc_hotk_check(void)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	int result;

	result = acpi_bus_get_status(ehotk->device);
	if (result)
		return result;
	if (ehotk->device->status.present) {
		if (write_acpi_int(ehotk->handle, "INIT", ehotk->init_flag,
				    &buffer)) {
			pr_err("Hotkey initialization failed\n");
			return -ENODEV;
		} else {
			pr_notice("Hotkey init flags 0x%x\n", ehotk->init_flag);
		}
		/* get control methods supported */
		if (read_acpi_int(ehotk->handle, "CMSG"
				   , &ehotk->cm_supported)) {
			pr_err("Get control methods supported failed\n");
			return -ENODEV;
		} else {
			cmsg_quirks();
			pr_info("Get control methods supported: 0x%x\n",
				ehotk->cm_supported);
		}
	} else {
		pr_err("Hotkey device not present, aborting\n");
		return -EINVAL;
	}
	return 0;
}