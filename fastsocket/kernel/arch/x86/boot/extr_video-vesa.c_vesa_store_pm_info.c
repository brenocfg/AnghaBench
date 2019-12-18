#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct biosregs {int ax; int /*<<< orphan*/  di; int /*<<< orphan*/  es; } ;
struct TYPE_3__ {int /*<<< orphan*/  vesapm_off; int /*<<< orphan*/  vesapm_seg; } ;
struct TYPE_4__ {TYPE_1__ screen_info; } ;

/* Variables and functions */
 TYPE_2__ boot_params ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 

__attribute__((used)) static void vesa_store_pm_info(void)
{
	struct biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ax = 0x4f0a;
	intcall(0x10, &ireg, &oreg);

	if (oreg.ax != 0x004f)
		return;

	boot_params.screen_info.vesapm_seg = oreg.es;
	boot_params.screen_info.vesapm_off = oreg.di;
}