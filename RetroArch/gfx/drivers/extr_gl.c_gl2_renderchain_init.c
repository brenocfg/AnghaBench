#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int idx; struct gfx_fbo_scale* scale; } ;
typedef  TYPE_3__ video_shader_ctx_scale_t ;
struct TYPE_22__ {int num; } ;
typedef  TYPE_4__ video_shader_ctx_info_t ;
struct gfx_fbo_scale {int valid; float scale_x; float scale_y; void* type_y; void* type_x; } ;
struct TYPE_23__ {unsigned int video_width; unsigned int video_height; int fbo_feedback_enable; unsigned int fbo_feedback_pass; int fbo_inited; TYPE_2__* fbo_rect; int /*<<< orphan*/  shader_data; TYPE_1__* shader; int /*<<< orphan*/  has_fbo; } ;
typedef  TYPE_5__ gl_t ;
struct TYPE_24__ {int fbo_pass; int /*<<< orphan*/  fbo_texture; struct gfx_fbo_scale* fbo_scale; } ;
typedef  TYPE_6__ gl2_renderchain_data_t ;
struct TYPE_20__ {void* height; void* width; int /*<<< orphan*/  img_height; int /*<<< orphan*/  img_width; } ;
struct TYPE_19__ {int (* get_feedback_pass ) (int /*<<< orphan*/ ,unsigned int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,void*,void*) ; 
 void* RARCH_SCALE_INPUT ; 
 int /*<<< orphan*/  RARCH_WARN (char*,size_t,int) ; 
 int /*<<< orphan*/  gl2_create_fbo_targets (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  gl2_create_fbo_textures (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  gl2_renderchain_recompute_pass_sizes (TYPE_5__*,TYPE_6__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gl2_shader_info (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  gl2_shader_scale (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ ) ; 
 void* next_pow2 (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void gl2_renderchain_init(
      gl_t *gl,
      gl2_renderchain_data_t *chain,
      unsigned fbo_width, unsigned fbo_height)
{
   int i;
   unsigned width, height;
   video_shader_ctx_scale_t scaler;
   video_shader_ctx_info_t shader_info;
   struct gfx_fbo_scale scale, scale_last;

   if (!gl2_shader_info(gl, &shader_info))
      return;

   if (!gl || shader_info.num == 0)
      return;

   width        = gl->video_width;
   height       = gl->video_height;

   scaler.idx   = 1;
   scaler.scale = &scale;

   gl2_shader_scale(gl, &scaler);

   scaler.idx   = shader_info.num;
   scaler.scale = &scale_last;

   gl2_shader_scale(gl, &scaler);

   /* we always want FBO to be at least initialized on startup for consoles */
   if (shader_info.num == 1 && !scale.valid)
      return;

   if (!gl->has_fbo)
   {
      RARCH_ERR("[GL]: Failed to locate FBO functions. Won't be able to use render-to-texture.\n");
      return;
   }

   chain->fbo_pass = shader_info.num - 1;
   if (scale_last.valid)
      chain->fbo_pass++;

   if (!scale.valid)
   {
      scale.scale_x = 1.0f;
      scale.scale_y = 1.0f;
      scale.type_x  = scale.type_y = RARCH_SCALE_INPUT;
      scale.valid   = true;
   }

   chain->fbo_scale[0] = scale;

   for (i = 1; i < chain->fbo_pass; i++)
   {
      scaler.idx   = i + 1;
      scaler.scale = &chain->fbo_scale[i];

      gl2_shader_scale(gl, &scaler);

      if (!chain->fbo_scale[i].valid)
      {
         chain->fbo_scale[i].scale_x = chain->fbo_scale[i].scale_y = 1.0f;
         chain->fbo_scale[i].type_x  = chain->fbo_scale[i].type_y  =
            RARCH_SCALE_INPUT;
         chain->fbo_scale[i].valid   = true;
      }
   }

   gl2_renderchain_recompute_pass_sizes(gl,
         chain, fbo_width, fbo_height, width, height);

   for (i = 0; i < chain->fbo_pass; i++)
   {
      gl->fbo_rect[i].width  = next_pow2(gl->fbo_rect[i].img_width);
      gl->fbo_rect[i].height = next_pow2(gl->fbo_rect[i].img_height);
      RARCH_LOG("[GL]: Creating FBO %d @ %ux%u\n", i,
            gl->fbo_rect[i].width, gl->fbo_rect[i].height);
   }

   gl->fbo_feedback_enable = gl->shader->get_feedback_pass(gl->shader_data,
         &gl->fbo_feedback_pass);

   if (gl->fbo_feedback_enable && gl->fbo_feedback_pass
         < (unsigned)chain->fbo_pass)
   {
      RARCH_LOG("[GL]: Creating feedback FBO %d @ %ux%u\n", i,
            gl->fbo_rect[gl->fbo_feedback_pass].width,
            gl->fbo_rect[gl->fbo_feedback_pass].height);
   }
   else if (gl->fbo_feedback_enable)
   {
      RARCH_WARN("[GL]: Tried to create feedback FBO of pass #%u, but there are only %d FBO passes. Will use input texture as feedback texture.\n",
              gl->fbo_feedback_pass, chain->fbo_pass);
      gl->fbo_feedback_enable = false;
   }

   gl2_create_fbo_textures(gl, chain);
   if (!gl || !gl2_create_fbo_targets(gl, chain))
   {
      glDeleteTextures(chain->fbo_pass, chain->fbo_texture);
      RARCH_ERR("[GL]: Failed to create FBO targets. Will continue without FBO.\n");
      return;
   }

   gl->fbo_inited = true;
}