#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ userdata; } ;
typedef  TYPE_6__ video_frame_info_t ;
struct TYPE_20__ {int /*<<< orphan*/  coords; } ;
typedef  TYPE_7__ video_coord_array_t ;
struct video_coords {int dummy; } ;
struct TYPE_16__ {float v0; int /*<<< orphan*/  v1; } ;
struct TYPE_17__ {TYPE_3__ f; } ;
struct TYPE_15__ {char* ident; int idx; int add_prefix; int enable; int /*<<< orphan*/  type; } ;
struct uniform_info {int enabled; TYPE_4__ result; TYPE_2__ lookup; int /*<<< orphan*/  type; int /*<<< orphan*/  count; int /*<<< orphan*/  location; } ;
struct TYPE_14__ {int id; } ;
struct TYPE_21__ {float width; int /*<<< orphan*/  height; TYPE_1__ pipeline; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_8__ menu_display_ctx_draw_t ;
struct TYPE_22__ {int /*<<< orphan*/  shader_data; TYPE_5__* shader; } ;
typedef  TYPE_9__ gl_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* set_uniform_parameter ) (int /*<<< orphan*/ ,struct uniform_info*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* use ) (TYPE_9__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ONE ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  SHADER_PROGRAM_VERTEX ; 
 int /*<<< orphan*/  UNIFORM_1F ; 
 int /*<<< orphan*/  UNIFORM_2F ; 
#define  VIDEO_SHADER_MENU 133 
#define  VIDEO_SHADER_MENU_2 132 
#define  VIDEO_SHADER_MENU_3 131 
#define  VIDEO_SHADER_MENU_4 130 
#define  VIDEO_SHADER_MENU_5 129 
#define  VIDEO_SHADER_MENU_6 128 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* menu_display_get_coords_array () ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct uniform_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct uniform_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_display_gl_draw_pipeline(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
#ifdef HAVE_SHADERPIPELINE
   struct uniform_info uniform_param;
   gl_t             *gl             = (gl_t*)video_info->userdata;
   static float t                   = 0;
   video_coord_array_t *ca          = menu_display_get_coords_array();

   draw->x                          = 0;
   draw->y                          = 0;
   draw->coords                     = (struct video_coords*)(&ca->coords);
   draw->matrix_data                = NULL;

   switch (draw->pipeline.id)
   {
      case VIDEO_SHADER_MENU:
      case VIDEO_SHADER_MENU_2:
         glBlendFunc(GL_ONE, GL_ONE);
         break;
      default:
         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         break;
   }

   switch (draw->pipeline.id)
   {
      case VIDEO_SHADER_MENU:
      case VIDEO_SHADER_MENU_2:
      case VIDEO_SHADER_MENU_3:
      case VIDEO_SHADER_MENU_4:
      case VIDEO_SHADER_MENU_5:
      case VIDEO_SHADER_MENU_6:
         gl->shader->use(gl, gl->shader_data, draw->pipeline.id,
               true);

         t += 0.01;

         uniform_param.type              = UNIFORM_1F;
         uniform_param.enabled           = true;
         uniform_param.location          = 0;
         uniform_param.count             = 0;

         uniform_param.lookup.type       = SHADER_PROGRAM_VERTEX;
         uniform_param.lookup.ident      = "time";
         uniform_param.lookup.idx        = draw->pipeline.id;
         uniform_param.lookup.add_prefix = true;
         uniform_param.lookup.enable     = true;

         uniform_param.result.f.v0       = t;

         gl->shader->set_uniform_parameter(gl->shader_data,
               &uniform_param, NULL);
         break;
   }

   switch (draw->pipeline.id)
   {
      case VIDEO_SHADER_MENU_3:
      case VIDEO_SHADER_MENU_4:
      case VIDEO_SHADER_MENU_5:
      case VIDEO_SHADER_MENU_6:
#ifndef HAVE_PSGL
         uniform_param.type              = UNIFORM_2F;
         uniform_param.lookup.ident      = "OutputSize";
         uniform_param.result.f.v0       = draw->width;
         uniform_param.result.f.v1       = draw->height;

         gl->shader->set_uniform_parameter(gl->shader_data,
               &uniform_param, NULL);
#endif
         break;
   }
#endif
}