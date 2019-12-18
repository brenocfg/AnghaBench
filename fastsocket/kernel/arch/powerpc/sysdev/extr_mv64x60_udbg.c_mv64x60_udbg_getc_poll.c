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
 int mv64x60_udbg_getc () ; 
 int /*<<< orphan*/  mv64x60_udbg_testc () ; 

__attribute__((used)) static int mv64x60_udbg_getc_poll(void)
{
	if (!mv64x60_udbg_testc())
		return -1;

	return mv64x60_udbg_getc();
}