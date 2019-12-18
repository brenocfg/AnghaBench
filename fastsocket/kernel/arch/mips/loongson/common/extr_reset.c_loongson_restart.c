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
 int /*<<< orphan*/  BONITO_BOOT_BASE ; 
 scalar_t__ ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_prepare_reboot () ; 
 void stub1 () ; 

__attribute__((used)) static void loongson_restart(char *command)
{
	/* do preparation for reboot */
	mach_prepare_reboot();

	/* reboot via jumping to boot base address */
	((void (*)(void))ioremap_nocache(BONITO_BOOT_BASE, 4)) ();
}