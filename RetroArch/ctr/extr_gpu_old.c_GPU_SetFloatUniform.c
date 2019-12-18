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
typedef  scalar_t__ GPU_SHADER_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddWrite (scalar_t__,int) ; 
 int /*<<< orphan*/  GPUCMD_AddWrites (scalar_t__,int*,int) ; 
 scalar_t__ GPUREG_VSH_FLOATUNIFORM_CONFIG ; 
 scalar_t__ GPUREG_VSH_FLOATUNIFORM_DATA ; 
 scalar_t__ GPU_GEOMETRY_SHADER ; 

void GPU_SetFloatUniform(GPU_SHADER_TYPE type, u32 startreg, u32* data, u32 numreg)
{
	if(!data)return;

	int regOffset=(type==GPU_GEOMETRY_SHADER)?(-0x30):(0x0);

	GPUCMD_AddWrite(GPUREG_VSH_FLOATUNIFORM_CONFIG+regOffset, 0x80000000|startreg);
	GPUCMD_AddWrites(GPUREG_VSH_FLOATUNIFORM_DATA+regOffset, data, numreg*4);
}