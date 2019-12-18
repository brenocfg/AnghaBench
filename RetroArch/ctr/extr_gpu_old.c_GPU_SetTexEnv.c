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
typedef  int u32 ;
typedef  int u16 ;
typedef  int GPU_COMBINEFUNC ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddIncrementalWrites (int,int*,int) ; 
 int GPUREG_0000 ; 
 int* GPU_TEVID ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

void GPU_SetTexEnv(u8 id, u16 rgbSources, u16 alphaSources, u16 rgbOperands, u16 alphaOperands, GPU_COMBINEFUNC rgbCombine, GPU_COMBINEFUNC alphaCombine, u32 constantColor)
{
	if(id>6)return;
	u32 param[0x5];
	memset(param, 0x00, 5*4);

	param[0x0]=(alphaSources<<16)|(rgbSources);
	param[0x1]=(alphaOperands<<12)|(rgbOperands);
	param[0x2]=(alphaCombine<<16)|(rgbCombine);
	param[0x3]=constantColor;
	param[0x4]=0x00000000; // ?

	GPUCMD_AddIncrementalWrites(GPUREG_0000|GPU_TEVID[id], param, 0x00000005);
}