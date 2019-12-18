#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned int width; unsigned int height; unsigned int tex_width; unsigned int tex_height; unsigned int out_width; unsigned int out_height; unsigned int frame_counter; void* info; void* prev_info; void* feedback_info; void* fbo_info; unsigned int fbo_info_cnt; } ;
typedef  TYPE_6__ video_shader_ctx_params_t ;
struct video_tex_info {int dummy; } ;
struct TYPE_15__ {size_t active_idx; TYPE_4__* shader; TYPE_5__* prg; int /*<<< orphan*/ * lut_textures; } ;
typedef  TYPE_7__ cg_shader_data_t ;
struct TYPE_13__ {int /*<<< orphan*/  fprg; int /*<<< orphan*/  vprg; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * fbo; int /*<<< orphan*/  feedback; int /*<<< orphan*/  orig; scalar_t__ frame_cnt_v; scalar_t__ frame_cnt_f; scalar_t__ frame_dir_v; int /*<<< orphan*/  out_size_v; int /*<<< orphan*/  tex_size_v; int /*<<< orphan*/  vid_size_v; scalar_t__ frame_dir_f; int /*<<< orphan*/  out_size_f; int /*<<< orphan*/  tex_size_f; int /*<<< orphan*/  vid_size_f; } ;
struct TYPE_12__ {unsigned int luts; unsigned int num_parameters; TYPE_1__* parameters; TYPE_3__* lut; TYPE_2__* pass; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {unsigned int frame_count_mod; } ;
struct TYPE_9__ {float current; int /*<<< orphan*/  id; } ;
typedef  scalar_t__ CGparameter ;

/* Variables and functions */
 unsigned int PREV_TEXTURES ; 
 size_t VIDEO_SHADER_STOCK_BLEND ; 
 scalar_t__ cgGetNamedParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cg_gl_set_param_1f (scalar_t__,float) ; 
 int /*<<< orphan*/  cg_gl_set_texture_parameter (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_cg_set_texture_info (TYPE_7__*,int /*<<< orphan*/ *,struct video_tex_info const*) ; 
 int /*<<< orphan*/  set_param_2f (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ state_manager_frame_is_reversed () ; 

__attribute__((used)) static void gl_cg_set_params(void *dat, void *shader_data)
{
   unsigned i;
   video_shader_ctx_params_t          *params =
      (video_shader_ctx_params_t*)dat;
   unsigned width                             = params->width;
   unsigned height                            = params->height;
   unsigned tex_width                         = params->tex_width;
   unsigned tex_height                        = params->tex_height;
   unsigned out_width                         = params->out_width;
   unsigned out_height                        = params->out_height;
   unsigned frame_count                       = params->frame_counter;
   const void *_info                          = params->info;
   const void *_prev_info                     = params->prev_info;
   const void *_feedback_info                 = params->feedback_info;
   const void *_fbo_info                      = params->fbo_info;
   unsigned fbo_info_cnt                      = params->fbo_info_cnt;
   const struct video_tex_info *info          = (const struct video_tex_info*)_info;
   const struct video_tex_info *prev_info     = (const struct video_tex_info*)_prev_info;
   const struct video_tex_info *feedback_info = (const struct video_tex_info*)_feedback_info;
   const struct video_tex_info *fbo_info      = (const struct video_tex_info*)_fbo_info;
   cg_shader_data_t *cg                       = (cg_shader_data_t*)shader_data;

   if (!cg || (cg->active_idx == 0))
         return;
   if (cg->active_idx == VIDEO_SHADER_STOCK_BLEND)
      return;

   /* Set frame. */
   set_param_2f(cg->prg[cg->active_idx].vid_size_f, width, height);
   set_param_2f(cg->prg[cg->active_idx].tex_size_f, tex_width, tex_height);
   set_param_2f(cg->prg[cg->active_idx].out_size_f, out_width, out_height);
   cg_gl_set_param_1f(cg->prg[cg->active_idx].frame_dir_f,
         state_manager_frame_is_reversed() ? -1.0 : 1.0);

   set_param_2f(cg->prg[cg->active_idx].vid_size_v, width, height);
   set_param_2f(cg->prg[cg->active_idx].tex_size_v, tex_width, tex_height);
   set_param_2f(cg->prg[cg->active_idx].out_size_v, out_width, out_height);
   cg_gl_set_param_1f(cg->prg[cg->active_idx].frame_dir_v,
         state_manager_frame_is_reversed() ? -1.0 : 1.0);

   if (cg->prg[cg->active_idx].frame_cnt_f || cg->prg[cg->active_idx].frame_cnt_v)
   {
      unsigned modulo = cg->shader->pass[cg->active_idx - 1].frame_count_mod;
      if (modulo)
         frame_count %= modulo;

      cg_gl_set_param_1f(cg->prg[cg->active_idx].frame_cnt_f, (float)frame_count);
      cg_gl_set_param_1f(cg->prg[cg->active_idx].frame_cnt_v, (float)frame_count);
   }

   /* Set lookup textures. */
   for (i = 0; i < cg->shader->luts; i++)
   {
      CGparameter fparam = cgGetNamedParameter(
            cg->prg[cg->active_idx].fprg, cg->shader->lut[i].id);
      CGparameter vparam = cgGetNamedParameter(cg->prg[cg->active_idx].vprg,
		  cg->shader->lut[i].id);

      cg_gl_set_texture_parameter(fparam, cg->lut_textures[i]);
      cg_gl_set_texture_parameter(vparam, cg->lut_textures[i]);
   }

   if (cg->active_idx)
   {
      /* Set original texture. */
      gl_cg_set_texture_info(cg, &cg->prg[cg->active_idx].orig, info);

      /* Set feedback texture. */
      gl_cg_set_texture_info(cg, &cg->prg[cg->active_idx].feedback, feedback_info);

      /* Bind FBO textures. */
      for (i = 0; i < fbo_info_cnt; i++)
         gl_cg_set_texture_info(cg, &cg->prg[cg->active_idx].fbo[i], &fbo_info[i]);
   }

   /* Set previous textures. */
   for (i = 0; i < PREV_TEXTURES; i++)
      gl_cg_set_texture_info(cg, &cg->prg[cg->active_idx].prev[i], &prev_info[i]);

   /* #pragma parameters. */
   for (i = 0; i < cg->shader->num_parameters; i++)
   {
      CGparameter param_v = cgGetNamedParameter(
            cg->prg[cg->active_idx].vprg, cg->shader->parameters[i].id);
      CGparameter param_f = cgGetNamedParameter(
            cg->prg[cg->active_idx].fprg, cg->shader->parameters[i].id);
      cg_gl_set_param_1f(param_v, cg->shader->parameters[i].current);
      cg_gl_set_param_1f(param_f, cg->shader->parameters[i].current);
   }
}