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
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 scalar_t__ devbug ; 

__attribute__((used)) static void Devices_B_Init(void)
{
	if (devbug)
		Log_print("B: INIT");

	CPU_regY = 1;
	CPU_ClrN;
}