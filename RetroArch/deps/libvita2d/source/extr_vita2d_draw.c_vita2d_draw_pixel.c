#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float x; float y; float z; unsigned int color; } ;
typedef  TYPE_1__ vita2d_color_vertex ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCE_GXM_INDEX_FORMAT_U16 ; 
 int /*<<< orphan*/  SCE_GXM_POLYGON_MODE_POINT ; 
 int /*<<< orphan*/  SCE_GXM_POLYGON_MODE_TRIANGLE_FILL ; 
 int /*<<< orphan*/  SCE_GXM_PRIMITIVE_POINTS ; 
 int /*<<< orphan*/  _vita2d_colorFragmentProgram ; 
 int /*<<< orphan*/  _vita2d_colorVertexProgram ; 
 int /*<<< orphan*/  _vita2d_colorWvpParam ; 
 int /*<<< orphan*/  _vita2d_context ; 
 int /*<<< orphan*/  _vita2d_ortho_matrix ; 
 int /*<<< orphan*/  sceGxmDraw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  sceGxmReserveVertexDefaultUniformBuffer (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  sceGxmSetFragmentProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetFrontPolygonMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetUniformDataF (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetVertexProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetVertexStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ vita2d_pool_memalign (int,int) ; 

void vita2d_draw_pixel(float x, float y, unsigned int color)
{
	vita2d_color_vertex *vertex = (vita2d_color_vertex *)vita2d_pool_memalign(
		1 * sizeof(vita2d_color_vertex), // 1 vertex
		sizeof(vita2d_color_vertex));

	uint16_t *index = (uint16_t *)vita2d_pool_memalign(
		1 * sizeof(uint16_t), // 1 index
		sizeof(uint16_t));

	vertex->x = x;
	vertex->y = y;
	vertex->z = +0.5f;
	vertex->color = color;

	*index = 0;

	sceGxmSetVertexProgram(_vita2d_context, _vita2d_colorVertexProgram);
	sceGxmSetFragmentProgram(_vita2d_context, _vita2d_colorFragmentProgram);

	void *vertexDefaultBuffer;
	sceGxmReserveVertexDefaultUniformBuffer(_vita2d_context, &vertexDefaultBuffer);
	sceGxmSetUniformDataF(vertexDefaultBuffer, _vita2d_colorWvpParam, 0, 16, _vita2d_ortho_matrix);

	sceGxmSetVertexStream(_vita2d_context, 0, vertex);
	sceGxmSetFrontPolygonMode(_vita2d_context, SCE_GXM_POLYGON_MODE_POINT);
	sceGxmDraw(_vita2d_context, SCE_GXM_PRIMITIVE_POINTS, SCE_GXM_INDEX_FORMAT_U16, index, 1);
	sceGxmSetFrontPolygonMode(_vita2d_context, SCE_GXM_POLYGON_MODE_TRIANGLE_FILL);
}