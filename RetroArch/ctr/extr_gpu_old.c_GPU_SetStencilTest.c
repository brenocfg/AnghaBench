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
typedef  int u8 ;
typedef  int GPU_TESTFUNC ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUREG_STENCIL_TEST ; 

void GPU_SetStencilTest(bool enable, GPU_TESTFUNC function, u8 ref, u8 input_mask, u8 write_mask)
{
	GPUCMD_AddWrite(GPUREG_STENCIL_TEST, (enable&1)|((function&7)<<4)|(write_mask<<8)|(ref<<16)|(input_mask<<24));
}