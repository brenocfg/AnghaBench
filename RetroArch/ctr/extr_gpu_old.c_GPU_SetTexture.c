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
typedef  int u16 ;
typedef  int GPU_TEXUNIT ;
typedef  int GPU_TEXCOLOR ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT0_ADDR1 ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT0_DIM ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT0_PARAM ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT0_TYPE ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT1_ADDR ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT1_DIM ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT1_PARAM ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT1_TYPE ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT2_ADDR ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT2_DIM ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT2_PARAM ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT2_TYPE ; 
#define  GPU_TEXUNIT0 130 
#define  GPU_TEXUNIT1 129 
#define  GPU_TEXUNIT2 128 

void GPU_SetTexture(GPU_TEXUNIT unit, u32* data, u16 width, u16 height, u32 param, GPU_TEXCOLOR colorType)
{
	switch (unit)
	{
	case GPU_TEXUNIT0:
		GPUCMD_AddWrite(GPUREG_TEXUNIT0_TYPE, colorType);
		GPUCMD_AddWrite(GPUREG_TEXUNIT0_ADDR1, ((u32)data)>>3);
		GPUCMD_AddWrite(GPUREG_TEXUNIT0_DIM, (width<<16)|height);
		GPUCMD_AddWrite(GPUREG_TEXUNIT0_PARAM, param);
		break;

	case GPU_TEXUNIT1:
		GPUCMD_AddWrite(GPUREG_TEXUNIT1_TYPE, colorType);
		GPUCMD_AddWrite(GPUREG_TEXUNIT1_ADDR, ((u32)data)>>3);
		GPUCMD_AddWrite(GPUREG_TEXUNIT1_DIM, (width<<16)|height);
		GPUCMD_AddWrite(GPUREG_TEXUNIT1_PARAM, param);
		break;

	case GPU_TEXUNIT2:
		GPUCMD_AddWrite(GPUREG_TEXUNIT2_TYPE, colorType);
		GPUCMD_AddWrite(GPUREG_TEXUNIT2_ADDR, ((u32)data)>>3);
		GPUCMD_AddWrite(GPUREG_TEXUNIT2_DIM, (width<<16)|height);
		GPUCMD_AddWrite(GPUREG_TEXUNIT2_PARAM, param);
		break;
	}
}