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
 int CPU_regX ; 
 int CPU_regY ; 
 int FALSE ; 
 int TRUE ; 
 int h_iocb ; 

__attribute__((used)) static int Devices_GetIOCB(void)
{
	if ((CPU_regX & 0x8f) != 0) {
		CPU_regY = 134; /* invalid IOCB number */
		CPU_SetN;
		return FALSE;
	}
	h_iocb = CPU_regX >> 4;
	return TRUE;
}