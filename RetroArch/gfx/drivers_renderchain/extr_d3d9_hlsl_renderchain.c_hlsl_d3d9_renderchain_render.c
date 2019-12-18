#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_16__ {unsigned int tex_w; unsigned int tex_h; } ;
struct shader_pass {TYPE_13__ info; int /*<<< orphan*/  tex; int /*<<< orphan*/  last_height; int /*<<< orphan*/  last_width; } ;
struct TYPE_15__ {TYPE_4__* final_viewport; int /*<<< orphan*/  dev; int /*<<< orphan*/  frame_count; TYPE_1__* passes; int /*<<< orphan*/  pixel_size; } ;
struct TYPE_18__ {TYPE_11__ chain; int /*<<< orphan*/  stock_shader; } ;
typedef  TYPE_2__ hlsl_renderchain_t ;
struct TYPE_19__ {scalar_t__ renderchain_data; } ;
typedef  TYPE_3__ d3d9_video_t ;
struct TYPE_20__ {unsigned int Width; unsigned int Height; float MinZ; float MaxZ; int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int count; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  LPDIRECT3DSURFACE9 ;
typedef  TYPE_4__ D3DVIEWPORT9 ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCLEAR_TARGET ; 
 int /*<<< orphan*/  d3d9_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_convert_geometry (TYPE_13__*,unsigned int*,unsigned int*,unsigned int,unsigned int,TYPE_4__*) ; 
 int /*<<< orphan*/  d3d9_device_get_render_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  d3d9_device_set_render_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_hlsl_bind_program (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_renderchain_blit_to_texture (int /*<<< orphan*/ ,void const*,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_renderchain_end_render (TYPE_11__*) ; 
 int /*<<< orphan*/  d3d9_renderchain_start_render (TYPE_11__*) ; 
 int /*<<< orphan*/  d3d9_set_viewports (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  d3d9_surface_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_texture_get_surface_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  hlsl_d3d9_renderchain_calc_and_set_shader_mvp (TYPE_2__*,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlsl_d3d9_renderchain_render_pass (TYPE_2__*,struct shader_pass*,unsigned int) ; 
 int /*<<< orphan*/  hlsl_d3d9_renderchain_set_vertices (TYPE_3__*,TYPE_2__*,struct shader_pass*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool hlsl_d3d9_renderchain_render(
      d3d9_video_t *d3d,
      const video_frame_info_t *video_info,
      const void *frame,
      unsigned width, unsigned height,
      unsigned pitch, unsigned rotation)
{
   LPDIRECT3DSURFACE9 back_buffer, target;
   unsigned i, current_width, current_height, out_width = 0, out_height = 0;
   struct shader_pass *last_pass    = NULL;
   struct shader_pass *first_pass   = NULL;
   hlsl_renderchain_t *chain        = (hlsl_renderchain_t*)
      d3d->renderchain_data;

   d3d9_renderchain_start_render(&chain->chain);

   current_width                  = width;
   current_height                 = height;

   first_pass                     = (struct shader_pass*)
      &chain->chain.passes->data[0];

   d3d9_convert_geometry(
         &first_pass->info,
         &out_width, &out_height,
         current_width, current_height, chain->chain.final_viewport);

   d3d9_renderchain_blit_to_texture(first_pass->tex,
         frame,
         first_pass->info.tex_w,
         first_pass->info.tex_h,
         width,
         height,
         first_pass->last_width,
         first_pass->last_height,
         pitch,
         chain->chain.pixel_size);

   /* Grab back buffer. */
   d3d9_device_get_render_target(chain->chain.dev, 0, (void**)&back_buffer);

   /* In-between render target passes. */
   for (i = 0; i < chain->chain.passes->count - 1; i++)
   {
      D3DVIEWPORT9   viewport = {0};
      struct shader_pass *from_pass  = (struct shader_pass*)
         &chain->chain.passes->data[i];
      struct shader_pass *to_pass    = (struct shader_pass*)
         &chain->chain.passes->data[i + 1];

      d3d9_texture_get_surface_level(to_pass->tex, 0, (void**)&target);

      d3d9_device_set_render_target(chain->chain.dev, 0, target);

      d3d9_convert_geometry(&from_pass->info,
            &out_width, &out_height,
            current_width, current_height, chain->chain.final_viewport);

      /* Clear out whole FBO. */
      viewport.Width  = to_pass->info.tex_w;
      viewport.Height = to_pass->info.tex_h;
      viewport.MinZ   = 0.0f;
      viewport.MaxZ   = 1.0f;

      d3d9_set_viewports(chain->chain.dev, &viewport);
      d3d9_clear(chain->chain.dev, 0, 0, D3DCLEAR_TARGET, 0, 1, 0);

      viewport.Width  = out_width;
      viewport.Height = out_height;

      d3d9_set_viewports(chain->chain.dev, &viewport);

      hlsl_d3d9_renderchain_set_vertices(
            d3d,
            chain, from_pass,
            current_width, current_height,
            out_width, out_height,
            out_width, out_height,
            chain->chain.frame_count, 0);

      hlsl_d3d9_renderchain_render_pass(chain,
            from_pass, 
            i + 1);

      current_width = out_width;
      current_height = out_height;
      d3d9_surface_free(target);
   }

   /* Final pass */
   d3d9_device_set_render_target(chain->chain.dev, 0, back_buffer);

   last_pass = (struct shader_pass*)&chain->chain.passes->
      data[chain->chain.passes->count - 1];

   d3d9_convert_geometry(&last_pass->info,
         &out_width, &out_height,
         current_width, current_height, chain->chain.final_viewport);

   d3d9_set_viewports(chain->chain.dev, chain->chain.final_viewport);

   hlsl_d3d9_renderchain_set_vertices(
         d3d,
         chain, last_pass,
         current_width, current_height,
         out_width, out_height,
         chain->chain.final_viewport->Width,
         chain->chain.final_viewport->Height,
         chain->chain.frame_count, rotation);

   hlsl_d3d9_renderchain_render_pass(chain, last_pass,
         chain->chain.passes->count);

   chain->chain.frame_count++;

   d3d9_surface_free(back_buffer);

   d3d9_renderchain_end_render(&chain->chain);
   d3d9_hlsl_bind_program(&chain->stock_shader, chain->chain.dev);
   hlsl_d3d9_renderchain_calc_and_set_shader_mvp(chain, &chain->stock_shader,
         chain->chain.final_viewport->Width,
         chain->chain.final_viewport->Height, 0);

   return true;
}