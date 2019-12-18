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
struct swoc_info {int /*<<< orphan*/  LinuxVer; int /*<<< orphan*/  LinuxSKU; int /*<<< orphan*/  rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  US_DEBUGP (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void debug_swoc(struct swoc_info *swocInfo)
{
	US_DEBUGP("SWIMS: SWoC Rev: %02d \n", swocInfo->rev);
	US_DEBUGP("SWIMS: Linux SKU: %04X \n", swocInfo->LinuxSKU);
	US_DEBUGP("SWIMS: Linux Version: %04X \n", swocInfo->LinuxVer);
}