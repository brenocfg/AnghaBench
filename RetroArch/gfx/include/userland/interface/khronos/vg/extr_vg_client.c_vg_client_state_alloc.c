#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t VGuint ;
struct TYPE_4__ {float stroke_line_width; float stroke_miter_limit; float stroke_dash_phase; int stroke_dash_phase_reset; int scissoring; float* tile_fill_color; float* clear_color; int color_transform; float* color_transform_values; int masking; int filter_format_linear; int filter_format_pre; int filter_channel_mask; int /*<<< orphan*/  pixel_layout; int /*<<< orphan*/  blend_mode; void* stroke_paint; void* fill_paint; int /*<<< orphan*/  rendering_quality; scalar_t__ scissor_rects_count; int /*<<< orphan*/  image_mode; int /*<<< orphan*/  image_quality; scalar_t__ stroke_dash_pattern_count; int /*<<< orphan*/  stroke_join_style; int /*<<< orphan*/  stroke_cap_style; int /*<<< orphan*/  fill_rule; TYPE_3__* matrices; int /*<<< orphan*/  matrix_mode; int /*<<< orphan*/ * flush_callback; int /*<<< orphan*/ * render_callback; int /*<<< orphan*/ * shared_state; } ;
typedef  TYPE_1__ VG_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  VG_CLIENT_SHARED_STATE_T ;
struct TYPE_5__ {int /*<<< orphan*/  server; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 size_t ARR_COUNT (TYPE_3__*) ; 
 int VG_ALPHA ; 
 int /*<<< orphan*/  VG_BLEND_SRC_OVER ; 
 int VG_BLUE ; 
 int /*<<< orphan*/  VG_CAP_BUTT ; 
 int /*<<< orphan*/  VG_DRAW_IMAGE_NORMAL ; 
 int /*<<< orphan*/  VG_EVEN_ODD ; 
 int VG_GREEN ; 
 int /*<<< orphan*/  VG_IMAGE_QUALITY_FASTER ; 
 void* VG_INVALID_HANDLE ; 
 int /*<<< orphan*/  VG_JOIN_MITER ; 
 int /*<<< orphan*/  VG_MATRIX_PATH_USER_TO_SURFACE ; 
 int /*<<< orphan*/  VG_PIXEL_LAYOUT_UNKNOWN ; 
 int VG_RED ; 
 int /*<<< orphan*/  VG_RENDERING_QUALITY_BETTER ; 
 scalar_t__ khrn_platform_malloc (int,char*) ; 
 int /*<<< orphan*/  vg_client_shared_state_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vg_mat3x3_set_identity (int /*<<< orphan*/ *) ; 

VG_CLIENT_STATE_T *vg_client_state_alloc(VG_CLIENT_SHARED_STATE_T *shared_state)
{
   VGuint i;

   VG_CLIENT_STATE_T *state = (VG_CLIENT_STATE_T *)khrn_platform_malloc(sizeof(VG_CLIENT_STATE_T), "VG_CLIENT_STATE_T");
   if (!state) {
      return NULL;
   }

   vg_client_shared_state_acquire(shared_state);
   state->shared_state = shared_state;

   state->render_callback = NULL;
   state->flush_callback = NULL;

   state->matrix_mode = VG_MATRIX_PATH_USER_TO_SURFACE;
   for (i = 0; i != ARR_COUNT(state->matrices); ++i) {
      vg_mat3x3_set_identity(&state->matrices[i].client);
      vg_mat3x3_set_identity(&state->matrices[i].server);
   }

   state->fill_rule = VG_EVEN_ODD;
   state->stroke_line_width = 1.0f;
   state->stroke_cap_style = VG_CAP_BUTT;
   state->stroke_join_style = VG_JOIN_MITER;
   state->stroke_miter_limit = 4.0f;
   state->stroke_dash_pattern_count = 0;
   state->stroke_dash_phase = 0.0f;
   state->stroke_dash_phase_reset = false;
   state->image_quality = VG_IMAGE_QUALITY_FASTER;
   state->image_mode = VG_DRAW_IMAGE_NORMAL;

   state->scissoring = false;
   state->scissor_rects_count = 0;

   state->rendering_quality = VG_RENDERING_QUALITY_BETTER;

   state->fill_paint = VG_INVALID_HANDLE;
   state->stroke_paint = VG_INVALID_HANDLE;
   state->tile_fill_color[0] = 0.0f;
   state->tile_fill_color[1] = 0.0f;
   state->tile_fill_color[2] = 0.0f;
   state->tile_fill_color[3] = 0.0f;
   state->clear_color[0] = 0.0f;
   state->clear_color[1] = 0.0f;
   state->clear_color[2] = 0.0f;
   state->clear_color[3] = 0.0f;

   state->color_transform = false;
   state->color_transform_values[0] = 1.0f;
   state->color_transform_values[1] = 1.0f;
   state->color_transform_values[2] = 1.0f;
   state->color_transform_values[3] = 1.0f;
   state->color_transform_values[4] = 0.0f;
   state->color_transform_values[5] = 0.0f;
   state->color_transform_values[6] = 0.0f;
   state->color_transform_values[7] = 0.0f;

   state->blend_mode = VG_BLEND_SRC_OVER;
   state->masking = false;

   state->filter_format_linear = false;
   state->filter_format_pre = false;
   state->filter_channel_mask = VG_RED | VG_GREEN | VG_BLUE | VG_ALPHA;

   state->pixel_layout = VG_PIXEL_LAYOUT_UNKNOWN;

   return state;
}