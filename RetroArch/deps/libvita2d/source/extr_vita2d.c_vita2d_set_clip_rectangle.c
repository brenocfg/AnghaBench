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
 int DISPLAY_HEIGHT ; 
 int DISPLAY_WIDTH ; 
 int /*<<< orphan*/  SCE_GXM_STENCIL_FUNC_ALWAYS ; 
 int /*<<< orphan*/  SCE_GXM_STENCIL_FUNC_EQUAL ; 
 int /*<<< orphan*/  SCE_GXM_STENCIL_FUNC_NEVER ; 
 int /*<<< orphan*/  SCE_GXM_STENCIL_OP_KEEP ; 
 int /*<<< orphan*/  SCE_GXM_STENCIL_OP_REPLACE ; 
 int /*<<< orphan*/  SCE_GXM_STENCIL_OP_ZERO ; 
 int /*<<< orphan*/  _vita2d_context ; 
 int clip_rect_x_max ; 
 int clip_rect_x_min ; 
 int clip_rect_y_max ; 
 int clip_rect_y_min ; 
 scalar_t__ clipping_enabled ; 
 scalar_t__ drawing ; 
 int /*<<< orphan*/  sceGxmSetFrontStencilFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vita2d_draw_rectangle (int,int,int,int,int /*<<< orphan*/ ) ; 

void vita2d_set_clip_rectangle(int x_min, int y_min, int x_max, int y_max)
{
	clip_rect_x_min = x_min;
	clip_rect_y_min = y_min;
	clip_rect_x_max = x_max;
	clip_rect_y_max = y_max;
	// we can only draw during a scene, but we can cache the values since they're not going to have any visible effect till the scene starts anyways
	if(drawing) {
		// clear the stencil buffer to 0
		sceGxmSetFrontStencilFunc(
			_vita2d_context,
			SCE_GXM_STENCIL_FUNC_NEVER,
			SCE_GXM_STENCIL_OP_ZERO,
			SCE_GXM_STENCIL_OP_ZERO,
			SCE_GXM_STENCIL_OP_ZERO,
			0xFF,
			0xFF);
		vita2d_draw_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
		// set the stencil to 1 in the desired region
		sceGxmSetFrontStencilFunc(
			_vita2d_context,
			SCE_GXM_STENCIL_FUNC_NEVER,
			SCE_GXM_STENCIL_OP_REPLACE,
			SCE_GXM_STENCIL_OP_REPLACE,
			SCE_GXM_STENCIL_OP_REPLACE,
			0xFF,
			0xFF);
		vita2d_draw_rectangle(x_min, y_min, x_max - x_min, y_max - y_min, 0);
		if(clipping_enabled) {
			// set the stencil function to only accept pixels where the stencil is 1
			sceGxmSetFrontStencilFunc(
				_vita2d_context,
				SCE_GXM_STENCIL_FUNC_EQUAL,
				SCE_GXM_STENCIL_OP_KEEP,
				SCE_GXM_STENCIL_OP_KEEP,
				SCE_GXM_STENCIL_OP_KEEP,
				0xFF,
				0xFF);
		} else {
			sceGxmSetFrontStencilFunc(
				_vita2d_context,
				SCE_GXM_STENCIL_FUNC_ALWAYS,
				SCE_GXM_STENCIL_OP_KEEP,
				SCE_GXM_STENCIL_OP_KEEP,
				SCE_GXM_STENCIL_OP_KEEP,
				0xFF,
				0xFF);
		}
	}
}