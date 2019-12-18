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
 int MSC0 ; 
 int /*<<< orphan*/  spitz_poweroff () ; 

__attribute__((used)) static void spitz_restart(char mode, const char *cmd)
{
	/* Bootloader magic for a reboot */
	if((MSC0 & 0xffff0000) == 0x7ff00000)
		MSC0 = (MSC0 & 0xffff) | 0x7ee00000;

	spitz_poweroff();
}