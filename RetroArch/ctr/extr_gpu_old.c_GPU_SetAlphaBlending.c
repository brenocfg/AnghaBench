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
typedef  int GPU_BLENDFACTOR ;
typedef  int GPU_BLENDEQUATION ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddMaskedWrite (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUREG_BLEND_FUNC ; 
 int /*<<< orphan*/  GPUREG_COLOR_OPERATION ; 

void GPU_SetAlphaBlending(GPU_BLENDEQUATION colorEquation, GPU_BLENDEQUATION alphaEquation,
	GPU_BLENDFACTOR colorSrc, GPU_BLENDFACTOR colorDst,
	GPU_BLENDFACTOR alphaSrc, GPU_BLENDFACTOR alphaDst)
{
	GPUCMD_AddWrite(GPUREG_BLEND_FUNC, colorEquation | (alphaEquation<<8) | (colorSrc<<16) | (colorDst<<20) | (alphaSrc<<24) | (alphaDst<<28));
	GPUCMD_AddMaskedWrite(GPUREG_COLOR_OPERATION, 0x2, 0x00000100);
}