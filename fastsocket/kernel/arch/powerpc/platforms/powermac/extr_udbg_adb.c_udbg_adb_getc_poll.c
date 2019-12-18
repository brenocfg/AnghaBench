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
 int udbg_adb_old_getc_poll () ; 
 int /*<<< orphan*/  udbg_adb_poll () ; 

__attribute__((used)) static int udbg_adb_getc_poll(void)
{
	udbg_adb_poll();

	if (udbg_adb_old_getc_poll)
		return udbg_adb_old_getc_poll();
	return -1;
}