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

/* Variables and functions */
 int /*<<< orphan*/  SCE_GXM_INDEX_FORMAT_U16 ; 
 int /*<<< orphan*/  SCE_GXM_PRIMITIVE_TRIANGLES ; 
 int /*<<< orphan*/  _vita2d_clearClearColorParam ; 
 int /*<<< orphan*/  _vita2d_context ; 
 int /*<<< orphan*/  clearFragmentProgram ; 
 int /*<<< orphan*/  clearVertexProgram ; 
 int /*<<< orphan*/  clearVertices ; 
 int /*<<< orphan*/  clear_color ; 
 int /*<<< orphan*/  linearIndices ; 
 int /*<<< orphan*/  sceGxmDraw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sceGxmReserveFragmentDefaultUniformBuffer (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  sceGxmSetFragmentProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetUniformDataF (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetVertexProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetVertexStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vita2d_clear_screen()
{
	// set clear shaders
	sceGxmSetVertexProgram(_vita2d_context, clearVertexProgram);
	sceGxmSetFragmentProgram(_vita2d_context, clearFragmentProgram);

	// set the clear color
	void *color_buffer;
	sceGxmReserveFragmentDefaultUniformBuffer(_vita2d_context, &color_buffer);
	sceGxmSetUniformDataF(color_buffer, _vita2d_clearClearColorParam, 0, 4, clear_color);

	// draw the clear triangle
	sceGxmSetVertexStream(_vita2d_context, 0, clearVertices);
	sceGxmDraw(_vita2d_context, SCE_GXM_PRIMITIVE_TRIANGLES, SCE_GXM_INDEX_FORMAT_U16, linearIndices, 3);
}