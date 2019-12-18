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
typedef  int GPU_WRITEMASK ;
typedef  int GPU_TESTFUNC ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUREG_DEPTH_COLOR_MASK ; 

void GPU_SetDepthTestAndWriteMask(bool enable, GPU_TESTFUNC function, GPU_WRITEMASK writemask)
{
	GPUCMD_AddWrite(GPUREG_DEPTH_COLOR_MASK, (enable&1)|((function&7)<<4)|(writemask<<8));
}