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
 int C ; 
 int CPU_regP ; 
 int N ; 
 scalar_t__ V ; 
 scalar_t__ Z ; 

void CPU_GetStatus(void)
{
#ifndef NO_V_FLAG_VARIABLE
	CPU_regP = (N & 0x80) + (V ? 0x40 : 0) + (CPU_regP & 0x3c) + ((Z == 0) ? 0x02 : 0) + C;
#else
	CPU_regP = (N & 0x80) + (CPU_regP & 0x7c) + ((Z == 0) ? 0x02 : 0) + C;
#endif
}