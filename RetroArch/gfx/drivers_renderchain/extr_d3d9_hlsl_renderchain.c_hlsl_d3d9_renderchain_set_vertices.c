#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  tex_h; int /*<<< orphan*/  tex_w; } ;
struct shader_pass {unsigned int last_width; unsigned int last_height; TYPE_1__ info; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {TYPE_4__ chain; } ;
typedef  TYPE_2__ hlsl_renderchain_t ;
typedef  int /*<<< orphan*/  d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_renderchain_set_vertices_on_change (TYPE_4__*,struct shader_pass*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  hlsl_d3d9_renderchain_calc_and_set_shader_mvp (TYPE_2__*,struct shader_pass*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  hlsl_d3d9_renderchain_set_shader_params (TYPE_4__*,int /*<<< orphan*/ ,struct shader_pass*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void hlsl_d3d9_renderchain_set_vertices(
      d3d9_video_t *d3d,
      hlsl_renderchain_t *chain,
      struct shader_pass *pass,
      unsigned width, unsigned height,
      unsigned out_width, unsigned out_height,
      unsigned vp_width, unsigned vp_height,
      uint64_t frame_count,
      unsigned rotation)
{
   if (pass->last_width != width || pass->last_height != height)
      d3d9_renderchain_set_vertices_on_change(&chain->chain,
            pass, width, height, out_width, out_height,
            vp_width, vp_height, rotation);

   hlsl_d3d9_renderchain_calc_and_set_shader_mvp(chain, pass,
         vp_width, vp_height, rotation);
   hlsl_d3d9_renderchain_set_shader_params(&chain->chain,
         chain->chain.dev,
         pass,
         width, height,
         pass->info.tex_w, pass->info.tex_h,
         vp_width, vp_height);
}