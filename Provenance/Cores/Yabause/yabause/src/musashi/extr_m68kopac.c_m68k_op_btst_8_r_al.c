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
 int DX ; 
 int FLAG_Z ; 
 int OPER_AL_8 () ; 

void m68k_op_btst_8_r_al(void)
{
	FLAG_Z = OPER_AL_8() & (1 << (DX & 7));
}