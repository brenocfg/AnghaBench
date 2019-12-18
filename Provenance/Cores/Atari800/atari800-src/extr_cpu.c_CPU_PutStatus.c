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
 int V ; 
 int Z ; 

void CPU_PutStatus(void)
{
	N = CPU_regP;
#ifndef NO_V_FLAG_VARIABLE
	V = (CPU_regP & 0x40);
#endif
	Z = (CPU_regP & 0x02) ^ 0x02;
	C = (CPU_regP & 0x01);
}