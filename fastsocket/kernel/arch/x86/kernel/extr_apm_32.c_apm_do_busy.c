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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ ALWAYS_CALL_BUSY ; 
 int /*<<< orphan*/  APM_FUNC_BUSY ; 
 int /*<<< orphan*/  apm_bios_call_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ clock_slowed ; 

__attribute__((used)) static void apm_do_busy(void)
{
	u32 dummy;
	int err;

	if (clock_slowed || ALWAYS_CALL_BUSY) {
		(void)apm_bios_call_simple(APM_FUNC_BUSY, 0, 0, &dummy, &err);
		clock_slowed = 0;
	}
}