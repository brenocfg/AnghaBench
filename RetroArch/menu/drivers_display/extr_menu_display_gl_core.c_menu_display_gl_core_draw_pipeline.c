#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yflip ;
struct TYPE_10__ {scalar_t__ height; scalar_t__ width; scalar_t__ userdata; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct TYPE_11__ {int /*<<< orphan*/  coords; } ;
typedef  TYPE_3__ video_coord_array_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  t ;
struct video_coords {int vertices; } ;
typedef  int /*<<< orphan*/  output_size ;
struct TYPE_9__ {int id; int backend_data_size; int /*<<< orphan*/ * backend_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  prim_type; struct video_coords* coords; TYPE_1__ pipeline; int /*<<< orphan*/ * matrix_data; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_4__ menu_display_ctx_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;
typedef  int /*<<< orphan*/  gl_core_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
#define  VIDEO_SHADER_MENU 132 
#define  VIDEO_SHADER_MENU_2 131 
#define  VIDEO_SHADER_MENU_3 130 
#define  VIDEO_SHADER_MENU_4 129 
#define  VIDEO_SHADER_MENU_5 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,float*,int) ; 
 TYPE_3__* menu_display_get_coords_array () ; 
 float* menu_display_gl_core_get_default_mvp (TYPE_2__*) ; 

__attribute__((used)) static void menu_display_gl_core_draw_pipeline(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
#ifdef HAVE_SHADERPIPELINE
   float output_size[2];
   static struct video_coords blank_coords;
   static uint8_t ubo_scratch_data[768];
   static float t                = 0.0f;
   float yflip                   = 0.0f;
   video_coord_array_t *ca       = NULL;
   gl_core_t *gl_core            = (gl_core_t*)video_info->userdata;

   if (!gl_core || !draw)
      return;

   draw->x                       = 0;
   draw->y                       = 0;
   draw->matrix_data             = NULL;

   output_size[0]                = (float)video_info->width;
   output_size[1]                = (float)video_info->height;

   switch (draw->pipeline.id)
   {
      /* Ribbon */
      default:
      case VIDEO_SHADER_MENU:
      case VIDEO_SHADER_MENU_2:
         ca = menu_display_get_coords_array();
         draw->coords                     = (struct video_coords*)&ca->coords;
         draw->pipeline.backend_data      = ubo_scratch_data;
         draw->pipeline.backend_data_size = 2 * sizeof(float);

         /* Match UBO layout in shader. */
         yflip = -1.0f;
         memcpy(ubo_scratch_data, &t, sizeof(t));
         memcpy(ubo_scratch_data + sizeof(float), &yflip, sizeof(yflip));
         break;

      /* Snow simple */
      case VIDEO_SHADER_MENU_3:
      case VIDEO_SHADER_MENU_4:
      case VIDEO_SHADER_MENU_5:
         draw->pipeline.backend_data      = ubo_scratch_data;
         draw->pipeline.backend_data_size = sizeof(math_matrix_4x4) 
            + 4 * sizeof(float);

         /* Match UBO layout in shader. */
         memcpy(ubo_scratch_data,
               menu_display_gl_core_get_default_mvp(video_info),
               sizeof(math_matrix_4x4));
         memcpy(ubo_scratch_data + sizeof(math_matrix_4x4),
               output_size,
               sizeof(output_size));

         if (draw->pipeline.id == VIDEO_SHADER_MENU_5)
            yflip = 1.0f;

         memcpy(ubo_scratch_data + sizeof(math_matrix_4x4) 
               + 2 * sizeof(float), &t, sizeof(t));
         memcpy(ubo_scratch_data + sizeof(math_matrix_4x4) 
               + 3 * sizeof(float), &yflip, sizeof(yflip));
         draw->coords = &blank_coords;
         blank_coords.vertices = 4;
         draw->prim_type = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
         break;
   }

   t += 0.01;
#endif
}