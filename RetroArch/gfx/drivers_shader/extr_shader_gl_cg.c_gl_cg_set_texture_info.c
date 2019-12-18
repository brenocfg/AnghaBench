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
struct video_tex_info {int /*<<< orphan*/  coord; int /*<<< orphan*/ * tex_size; int /*<<< orphan*/ * input_size; int /*<<< orphan*/  tex; } ;
struct cg_fbo_params {scalar_t__ coord; int /*<<< orphan*/  tex_size_f; int /*<<< orphan*/  tex_size_v; int /*<<< orphan*/  vid_size_f; int /*<<< orphan*/  vid_size_v; int /*<<< orphan*/  tex; } ;
typedef  int /*<<< orphan*/  cg_shader_data_t ;
typedef  int /*<<< orphan*/  CGparameter ;

/* Variables and functions */
 int /*<<< orphan*/  cg_gl_set_texture_parameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_cg_set_coord_array (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_param_2f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl_cg_set_texture_info(
      cg_shader_data_t *cg,
      const struct cg_fbo_params *params,
      const struct video_tex_info *info)
{
   CGparameter param                     = params->tex;

   cg_gl_set_texture_parameter(param, info->tex);

   set_param_2f(params->vid_size_v,
         info->input_size[0], info->input_size[1]);
   set_param_2f(params->vid_size_f,
         info->input_size[0], info->input_size[1]);
   set_param_2f(params->tex_size_v,
         info->tex_size[0],   info->tex_size[1]);
   set_param_2f(params->tex_size_f,
         info->tex_size[0],   info->tex_size[1]);

   if (params->coord)
      gl_cg_set_coord_array(params->coord, cg, info->coord, 2);
}