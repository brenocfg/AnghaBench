#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {float font_msg_pos_x; float font_msg_pos_y; scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_7__ video_frame_info_t ;
struct TYPE_24__ {float* color; float* vertex; float* tex_coord; float* lut_tex_coord; unsigned int vertices; } ;
typedef  TYPE_8__ video_coords_t ;
struct TYPE_21__ {float v0; float v1; float v2; float v3; } ;
struct TYPE_22__ {TYPE_5__ f; } ;
struct TYPE_19__ {char* ident; int add_prefix; int enable; int /*<<< orphan*/  idx; int /*<<< orphan*/  type; } ;
struct uniform_info {int enabled; TYPE_6__ result; TYPE_3__ lookup; scalar_t__ count; scalar_t__ location; int /*<<< orphan*/  type; } ;
struct TYPE_18__ {float video_font_size; float video_msg_bgcolor_opacity; } ;
struct TYPE_17__ {float video_msg_bgcolor_red; float video_msg_bgcolor_green; float video_msg_bgcolor_blue; } ;
struct TYPE_25__ {TYPE_2__ floats; TYPE_1__ uints; } ;
typedef  TYPE_9__ settings_t ;
struct TYPE_16__ {int /*<<< orphan*/  shader_data; TYPE_4__* shader; int /*<<< orphan*/  mvp_no_rot; } ;
typedef  TYPE_10__ gl_t ;
struct TYPE_20__ {int /*<<< orphan*/  (* set_uniform_parameter ) (int /*<<< orphan*/ ,struct uniform_info*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_mvp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_coords ) (int /*<<< orphan*/ ,TYPE_8__*) ;int /*<<< orphan*/  (* use ) (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_FUNC_ADD ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  SHADER_PROGRAM_FRAGMENT ; 
 int /*<<< orphan*/  UNIFORM_4F ; 
 int /*<<< orphan*/  VIDEO_SHADER_STOCK_BLEND ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_9__* config_get_ptr () ; 
 int font_driver_get_message_width (int /*<<< orphan*/ *,char const*,unsigned int,float) ; 
 int /*<<< orphan*/  free (float*) ; 
 int /*<<< orphan*/  glBlendEquation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct uniform_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,struct uniform_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_set_viewport (scalar_t__,scalar_t__,int,int) ; 

__attribute__((used)) static void gl2_render_osd_background(
      gl_t *gl, video_frame_info_t *video_info,
      const char *msg)
{
   video_coords_t coords;
   struct uniform_info uniform_param;
   float colors[4];
   const unsigned
      vertices_total       = 6;
   float *dummy            = (float*)calloc(4 * vertices_total, sizeof(float));
   float *verts            = (float*)malloc(2 * vertices_total * sizeof(float));
   settings_t *settings    = config_get_ptr();
   int msg_width           =
      font_driver_get_message_width(NULL, msg, (unsigned)strlen(msg), 1.0f);

   /* shader driver expects vertex coords as 0..1 */
   float x                 = video_info->font_msg_pos_x;
   float y                 = video_info->font_msg_pos_y;
   float width             = msg_width / (float)video_info->width;
   float height            =
      settings->floats.video_font_size / (float)video_info->height;

   float x2                = 0.005f; /* extend background around text */
   float y2                = 0.005f;

   x                      -= x2;
   y                      -= y2;
   width                  += x2;
   height                 += y2;

   colors[0]               = settings->uints.video_msg_bgcolor_red / 255.0f;
   colors[1]               = settings->uints.video_msg_bgcolor_green / 255.0f;
   colors[2]               = settings->uints.video_msg_bgcolor_blue / 255.0f;
   colors[3]               = settings->floats.video_msg_bgcolor_opacity;

   /* triangle 1 */
   verts[0]                = x;
   verts[1]                = y; /* bottom-left */

   verts[2]                = x;
   verts[3]                = y + height; /* top-left */

   verts[4]                = x + width;
   verts[5]                = y + height; /* top-right */

   /* triangle 2 */
   verts[6]                = x;
   verts[7]                = y; /* bottom-left */

   verts[8]                = x + width;
   verts[9]                = y + height; /* top-right */

   verts[10]               = x + width;
   verts[11]               = y; /* bottom-right */

   coords.color            = dummy;
   coords.vertex           = verts;
   coords.tex_coord        = dummy;
   coords.lut_tex_coord    = dummy;
   coords.vertices         = vertices_total;

   video_driver_set_viewport(video_info->width,
         video_info->height, true, false);

   gl->shader->use(gl, gl->shader_data,
         VIDEO_SHADER_STOCK_BLEND, true);

   gl->shader->set_coords(gl->shader_data, &coords);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glBlendEquation(GL_FUNC_ADD);

   gl->shader->set_mvp(gl->shader_data, &gl->mvp_no_rot);

   uniform_param.type              = UNIFORM_4F;
   uniform_param.enabled           = true;
   uniform_param.location          = 0;
   uniform_param.count             = 0;

   uniform_param.lookup.type       = SHADER_PROGRAM_FRAGMENT;
   uniform_param.lookup.ident      = "bgcolor";
   uniform_param.lookup.idx        = VIDEO_SHADER_STOCK_BLEND;
   uniform_param.lookup.add_prefix = true;
   uniform_param.lookup.enable     = true;

   uniform_param.result.f.v0       = colors[0];
   uniform_param.result.f.v1       = colors[1];
   uniform_param.result.f.v2       = colors[2];
   uniform_param.result.f.v3       = colors[3];

   gl->shader->set_uniform_parameter(gl->shader_data,
         &uniform_param, NULL);

   glDrawArrays(GL_TRIANGLES, 0, coords.vertices);

   /* reset uniform back to zero so it is not used for anything else */
   uniform_param.result.f.v0       = 0.0f;
   uniform_param.result.f.v1       = 0.0f;
   uniform_param.result.f.v2       = 0.0f;
   uniform_param.result.f.v3       = 0.0f;

   gl->shader->set_uniform_parameter(gl->shader_data,
         &uniform_param, NULL);

   free(dummy);
   free(verts);

   video_driver_set_viewport(video_info->width,
         video_info->height, false, true);
}