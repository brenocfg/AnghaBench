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
typedef  int /*<<< orphan*/  vita2d_texture_vertex ;
struct TYPE_3__ {int /*<<< orphan*/  gxm_tex; } ;
typedef  TYPE_1__ vita2d_texture ;
typedef  int /*<<< orphan*/  SceGxmPrimitiveType ;

/* Variables and functions */
 int /*<<< orphan*/  SCE_GXM_INDEX_FORMAT_U16 ; 
 int /*<<< orphan*/  SCE_GXM_POLYGON_MODE_TRIANGLE_FILL ; 
 int /*<<< orphan*/  _vita2d_context ; 
 int /*<<< orphan*/  sceGxmDraw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sceGxmSetBackPolygonMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetFragmentTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceGxmSetVertexStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_texture_tint_color_uniform (unsigned int) ; 
 int /*<<< orphan*/  set_texture_tint_program () ; 
 int /*<<< orphan*/  set_texture_wvp_uniform () ; 
 int /*<<< orphan*/  vita2d_get_linear_indices () ; 

void vita2d_draw_array_textured(const vita2d_texture *texture, SceGxmPrimitiveType mode, const vita2d_texture_vertex *vertices, size_t count, unsigned int color)
{
	set_texture_tint_program();
	set_texture_wvp_uniform();
	set_texture_tint_color_uniform(color);

	sceGxmSetBackPolygonMode(_vita2d_context, SCE_GXM_POLYGON_MODE_TRIANGLE_FILL);

	// Set the texture to the TEXUNIT0
	sceGxmSetFragmentTexture(_vita2d_context, 0, &texture->gxm_tex);

	sceGxmSetVertexStream(_vita2d_context, 0, vertices);
	sceGxmDraw(_vita2d_context, mode, SCE_GXM_INDEX_FORMAT_U16, vita2d_get_linear_indices(), count);
}