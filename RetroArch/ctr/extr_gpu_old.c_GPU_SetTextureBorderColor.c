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
typedef  int /*<<< orphan*/  u32 ;
typedef  int GPU_TEXUNIT ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT0_BORDER_COLOR ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT1_BORDER_COLOR ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT2_BORDER_COLOR ; 
#define  GPU_TEXUNIT0 130 
#define  GPU_TEXUNIT1 129 
#define  GPU_TEXUNIT2 128 

void GPU_SetTextureBorderColor(GPU_TEXUNIT unit,u32 borderColor)
{
	switch (unit)
	{
	case GPU_TEXUNIT0:
		GPUCMD_AddWrite(GPUREG_TEXUNIT0_BORDER_COLOR, borderColor);
		break;

	case GPU_TEXUNIT1:
		GPUCMD_AddWrite(GPUREG_TEXUNIT1_BORDER_COLOR, borderColor);
		break;

	case GPU_TEXUNIT2:
		GPUCMD_AddWrite(GPUREG_TEXUNIT2_BORDER_COLOR, borderColor);
		break;
	}
}