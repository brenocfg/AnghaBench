#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct video_coords {int vertices; float const* color; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; } ;
struct TYPE_8__ {int /*<<< orphan*/  menu_mouse_enable; scalar_t__ video_fullscreen; } ;
struct TYPE_10__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_9__ {scalar_t__ id; } ;
struct TYPE_11__ {float x; int y; float width; float height; uintptr_t texture; TYPE_2__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; } ;
typedef  TYPE_4__ menu_display_ctx_draw_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* blend_end ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* blend_begin ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 TYPE_3__* config_get_ptr () ; 
 TYPE_6__* menu_disp ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_has_windowed ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void menu_display_draw_cursor(
      video_frame_info_t *video_info,
      float *color, float cursor_size, uintptr_t texture,
      float x, float y, unsigned width, unsigned height)
{
   menu_display_ctx_draw_t draw;
   struct video_coords coords;
   settings_t *settings = config_get_ptr();
   bool cursor_visible  = settings->bools.video_fullscreen ||
       !menu_display_has_windowed;
   if (!settings->bools.menu_mouse_enable || !cursor_visible)
      return;

   coords.vertices      = 4;
   coords.vertex        = NULL;
   coords.tex_coord     = NULL;
   coords.lut_tex_coord = NULL;
   coords.color         = (const float*)color;

   if (menu_disp && menu_disp->blend_begin)
      menu_disp->blend_begin(video_info);

   draw.x               = x - (cursor_size / 2);
   draw.y               = (int)height - y - (cursor_size / 2);
   draw.width           = cursor_size;
   draw.height          = cursor_size;
   draw.coords          = &coords;
   draw.matrix_data     = NULL;
   draw.texture         = texture;
   draw.prim_type       = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
   draw.pipeline.id     = 0;

   menu_display_draw(&draw, video_info);

   if (menu_disp && menu_disp->blend_end)
      menu_disp->blend_end(video_info);
}