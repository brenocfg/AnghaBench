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
 int /*<<< orphan*/  btext_drawchar (char) ; 
 void udbg_adb_old_putc (char) ; 
 scalar_t__ udbg_adb_use_btext ; 

__attribute__((used)) static void udbg_adb_putc(char c)
{
#ifdef CONFIG_BOOTX_TEXT
	if (udbg_adb_use_btext)
		btext_drawchar(c);
#endif
	if (udbg_adb_old_putc)
		return udbg_adb_old_putc(c);
}