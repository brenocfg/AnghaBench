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
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 scalar_t__ devbug ; 

__attribute__((used)) static void Devices_B_Read(void)
{
	if (devbug)
		Log_print("B: READ");

	CPU_regY = 136; /* end of file */
	CPU_SetN;
}