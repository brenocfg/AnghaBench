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
typedef  int u8 ;
struct biosregs {int al; int ah; int ax; } ;
struct TYPE_3__ {int orig_video_mode; } ;
struct TYPE_4__ {TYPE_1__ screen_info; } ;

/* Variables and functions */
 TYPE_2__ boot_params ; 
 int do_restore ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 

__attribute__((used)) static int set_bios_mode(u8 mode)
{
	struct biosregs ireg, oreg;
	u8 new_mode;

	initregs(&ireg);
	ireg.al = mode;		/* AH=0x00 Set Video Mode */
	intcall(0x10, &ireg, NULL);

	ireg.ah = 0x0f;		/* Get Current Video Mode */
	intcall(0x10, &ireg, &oreg);

	do_restore = 1;		/* Assume video contents were lost */

	/* Not all BIOSes are clean with the top bit */
	new_mode = oreg.al & 0x7f;

	if (new_mode == mode)
		return 0;	/* Mode change OK */

#ifndef _WAKEUP
	if (new_mode != boot_params.screen_info.orig_video_mode) {
		/* Mode setting failed, but we didn't end up where we
		   started.  That's bad.  Try to revert to the original
		   video mode. */
		ireg.ax = boot_params.screen_info.orig_video_mode;
		intcall(0x10, &ireg, NULL);
	}
#endif
	return -1;
}