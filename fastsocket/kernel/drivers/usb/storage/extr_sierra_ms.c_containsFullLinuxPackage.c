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
struct swoc_info {int LinuxSKU; } ;

/* Variables and functions */

__attribute__((used)) static bool containsFullLinuxPackage(struct swoc_info *swocInfo)
{
	if ((swocInfo->LinuxSKU >= 0x2100 && swocInfo->LinuxSKU <= 0x2FFF) ||
	   (swocInfo->LinuxSKU >= 0x7100 && swocInfo->LinuxSKU <= 0x7FFF))
		return true;
	else
		return false;
}