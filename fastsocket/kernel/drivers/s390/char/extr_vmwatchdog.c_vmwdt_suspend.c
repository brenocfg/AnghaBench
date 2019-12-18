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

/* Variables and functions */
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  VMWDT_OPEN ; 
 int /*<<< orphan*/  VMWDT_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmwdt_is_open ; 

__attribute__((used)) static int vmwdt_suspend(void)
{
	if (test_and_set_bit(VMWDT_OPEN, &vmwdt_is_open)) {
		pr_err("The system cannot be suspended while the watchdog"
			" is in use\n");
		return NOTIFY_BAD;
	}
	if (test_bit(VMWDT_RUNNING, &vmwdt_is_open)) {
		clear_bit(VMWDT_OPEN, &vmwdt_is_open);
		pr_err("The system cannot be suspended while the watchdog"
			" is running\n");
		return NOTIFY_BAD;
	}
	return NOTIFY_DONE;
}