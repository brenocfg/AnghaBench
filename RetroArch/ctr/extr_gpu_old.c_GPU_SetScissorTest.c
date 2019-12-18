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
typedef  int u32 ;
typedef  int GPU_SCISSORMODE ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddIncrementalWrites (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  GPUREG_SCISSORTEST_MODE ; 

void GPU_SetScissorTest(GPU_SCISSORMODE mode, u32 left, u32 bottom, u32 right, u32 top)
{
	u32 param[3];

	param[0x0] = mode;
	param[0x1] = (bottom<<16)|(left&0xFFFF);
	param[0x2] = ((top-1)<<16)|((right-1)&0xFFFF);
	GPUCMD_AddIncrementalWrites(GPUREG_SCISSORTEST_MODE, param, 0x00000003);
}