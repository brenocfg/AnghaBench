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
typedef  int GPU_Primitive_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddMaskedWrite (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUREG_DRAWELEMENTS ; 
 int /*<<< orphan*/  GPUREG_GEOSTAGE_CONFIG ; 
 int /*<<< orphan*/  GPUREG_GEOSTAGE_CONFIG2 ; 
 int /*<<< orphan*/  GPUREG_INDEXBUFFER_CONFIG ; 
 int /*<<< orphan*/  GPUREG_NUMVERTICES ; 
 int /*<<< orphan*/  GPUREG_PRIMITIVE_CONFIG ; 
 int /*<<< orphan*/  GPUREG_RESTART_PRIMITIVE ; 
 int /*<<< orphan*/  GPUREG_START_DRAW_FUNC0 ; 
 int /*<<< orphan*/  GPUREG_VERTEX_OFFSET ; 
 int /*<<< orphan*/  GPUREG_VTX_FUNC ; 

void GPU_DrawElements(GPU_Primitive_t primitive, u32* indexArray, u32 n)
{
	//set primitive type
	GPUCMD_AddMaskedWrite(GPUREG_PRIMITIVE_CONFIG, 0x2, primitive);
	GPUCMD_AddMaskedWrite(GPUREG_RESTART_PRIMITIVE, 0x2, 0x00000001);
	//index buffer (TODO : support multiple types)
	GPUCMD_AddWrite(GPUREG_INDEXBUFFER_CONFIG, 0x80000000|((u32)indexArray));
	//pass number of vertices
	GPUCMD_AddWrite(GPUREG_NUMVERTICES, n);

	GPUCMD_AddWrite(GPUREG_VERTEX_OFFSET, 0x00000000);

	GPUCMD_AddMaskedWrite(GPUREG_GEOSTAGE_CONFIG, 0x2, 0x00000100);
	GPUCMD_AddMaskedWrite(GPUREG_GEOSTAGE_CONFIG2, 0x2, 0x00000100);

	GPUCMD_AddMaskedWrite(GPUREG_START_DRAW_FUNC0, 0x1, 0x00000000);
	GPUCMD_AddWrite(GPUREG_DRAWELEMENTS, 0x00000001);
	GPUCMD_AddMaskedWrite(GPUREG_START_DRAW_FUNC0, 0x1, 0x00000001);
	GPUCMD_AddWrite(GPUREG_VTX_FUNC, 0x00000001);

	// CHECKME: does this one also require GPUREG_FRAMEBUFFER_FLUSH at the end?
}