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
typedef  int uint16_t ;

/* Variables and functions */
 int M_PI ; 
 int /*<<< orphan*/  SCE_GXM_INDEX_FORMAT_U16 ; 
 int /*<<< orphan*/  SCE_GXM_PRIMITIVE_TRIANGLE_FAN ; 
 int /*<<< orphan*/  _vita2d_colorFragmentProgram ; 
 int /*<<< orphan*/  _vita2d_colorVertexProgram ; 
 int /*<<< orphan*/  _vita2d_colorWvpParam ; 
 int /*<<< orphan*/  _vita2d_context ; 
 int /*<<< orphan*/  _vita2d_ortho_matrix ; 
 float cosf (float) ; 
 int /*<<< orphan*/  sceGxmDraw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int const) ; 
 int /*<<< orphan*/  sceGxmReserveVertexDefaultUniformBuffer (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  sceGxmSetFragmentProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetUniformDataF (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetVertexProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetVertexStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 float sinf (float) ; 
 scalar_t__ vita2d_pool_memalign (int const,int) ; 

void vita2d_draw_fill_circle(float x, float y, float radius, unsigned int color)
{
	static const int num_segments = 100;

	vita2d_color_vertex *vertices = (vita2d_color_vertex *)vita2d_pool_memalign(
		(num_segments + 1) * sizeof(vita2d_color_vertex),
		sizeof(vita2d_color_vertex));

	uint16_t *indices = (uint16_t *)vita2d_pool_memalign(
		(num_segments + 2) * sizeof(uint16_t),
		sizeof(uint16_t));


	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].z = +0.5f;
	vertices[0].color = color;
	indices[0] = 0;

	float theta = 2 * M_PI / (float)num_segments;
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float xx = radius;
	float yy = 0;
	int i;

	for (i = 1; i <= num_segments; i++) {
		vertices[i].x = x + xx;
		vertices[i].y = y + yy;
		vertices[i].z = +0.5f;
		vertices[i].color = color;
		indices[i] = i;

		t = xx;
		xx = c * xx - s * yy;
		yy = s * t + c * yy;
	}

	indices[num_segments + 1] = 1;

	sceGxmSetVertexProgram(_vita2d_context, _vita2d_colorVertexProgram);
	sceGxmSetFragmentProgram(_vita2d_context, _vita2d_colorFragmentProgram);

	void *vertexDefaultBuffer;
	sceGxmReserveVertexDefaultUniformBuffer(_vita2d_context, &vertexDefaultBuffer);
	sceGxmSetUniformDataF(vertexDefaultBuffer, _vita2d_colorWvpParam, 0, 16, _vita2d_ortho_matrix);

	sceGxmSetVertexStream(_vita2d_context, 0, vertices);
	sceGxmDraw(_vita2d_context, SCE_GXM_PRIMITIVE_TRIANGLE_FAN, SCE_GXM_INDEX_FORMAT_U16, indices, num_segments + 2);
}