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
 int /*<<< orphan*/  VMWDT_RUNNING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __diag288 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmwdt_is_open ; 
 int /*<<< orphan*/  wdt_cancel ; 

__attribute__((used)) static int vmwdt_disable(void)
{
	int ret = __diag288(wdt_cancel, 0, "", 0);
	WARN_ON(ret != 0);
	clear_bit(VMWDT_RUNNING, &vmwdt_is_open);
	return ret;
}