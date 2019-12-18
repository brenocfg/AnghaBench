#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_13__ {int /*<<< orphan*/  coords; } ;
typedef  TYPE_5__ video_coord_array_t ;
struct video_coords {int dummy; } ;
struct TYPE_11__ {float v0; } ;
struct TYPE_12__ {TYPE_3__ f; } ;
struct TYPE_10__ {int enable; int add_prefix; int idx; char* ident; int /*<<< orphan*/  type; } ;
struct uniform_info {int enabled; TYPE_4__ result; TYPE_2__ lookup; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int id; } ;
struct TYPE_14__ {TYPE_1__ pipeline; struct video_coords* coords; int /*<<< orphan*/ * matrix_data; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_6__ menu_display_ctx_draw_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHADER_PROGRAM_VERTEX ; 
 int /*<<< orphan*/  UNIFORM_1F ; 
#define  VIDEO_SHADER_MENU 130 
#define  VIDEO_SHADER_MENU_2 129 
#define  VIDEO_SHADER_MENU_3 128 
 TYPE_5__* menu_display_get_coords_array () ; 

__attribute__((used)) static void menu_display_d3d9_draw_pipeline(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
#if defined(HAVE_HLSL) || defined(HAVE_CG)
   static float t                    = 0;
   video_coord_array_t *ca           = NULL;

   if (!draw)
      return;

   ca                                = menu_display_get_coords_array();

   draw->x                           = 0;
   draw->y                           = 0;
   draw->coords                      = NULL;
   draw->matrix_data                 = NULL;

   if (ca)
      draw->coords                   = (struct video_coords*)&ca->coords;

   switch (draw->pipeline.id)
   {
      case VIDEO_SHADER_MENU:
      case VIDEO_SHADER_MENU_2:
      case VIDEO_SHADER_MENU_3:
         {
            struct uniform_info uniform_param  = {0};
            t                                 += 0.01;

            (void)uniform_param;

            uniform_param.enabled              = true;
            uniform_param.lookup.enable        = true;
            uniform_param.lookup.add_prefix    = true;
            uniform_param.lookup.idx           = draw->pipeline.id;
            uniform_param.lookup.type          = SHADER_PROGRAM_VERTEX;
            uniform_param.type                 = UNIFORM_1F;
            uniform_param.lookup.ident         = "time";
            uniform_param.result.f.v0          = t;
         }
         break;
   }
#endif
}