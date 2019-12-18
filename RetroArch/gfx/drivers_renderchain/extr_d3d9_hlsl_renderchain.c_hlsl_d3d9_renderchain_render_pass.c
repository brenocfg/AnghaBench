#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* pass; } ;
struct shader_pass {int /*<<< orphan*/  vprg; int /*<<< orphan*/  fprg; int /*<<< orphan*/  vertex_buf; int /*<<< orphan*/  vertex_decl; TYPE_2__ info; int /*<<< orphan*/  tex; } ;
struct D3D9Vertex {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  dev; } ;
struct TYPE_16__ {TYPE_7__ chain; TYPE_4__* luts; int /*<<< orphan*/  dev; } ;
typedef  TYPE_5__ hlsl_renderchain_t ;
struct TYPE_15__ {unsigned int count; TYPE_3__* data; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int /*<<< orphan*/  filter; } ;
typedef  scalar_t__ CGparameter ;

/* Variables and functions */
 int /*<<< orphan*/  D3DPT_TRIANGLESTRIP ; 
 int /*<<< orphan*/  D3DTEXF_POINT ; 
 unsigned int cgGetParameterResourceIndex (scalar_t__) ; 
 int /*<<< orphan*/  d3d9_draw_primitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d3d9_hlsl_bind_program (struct shader_pass*,int /*<<< orphan*/ ) ; 
 scalar_t__ d3d9_hlsl_get_constant_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_hlsl_renderchain_bind_orig (TYPE_5__*,int /*<<< orphan*/ ,struct shader_pass*) ; 
 int /*<<< orphan*/  d3d9_hlsl_renderchain_bind_pass (TYPE_5__*,int /*<<< orphan*/ ,struct shader_pass*,unsigned int) ; 
 int /*<<< orphan*/  d3d9_hlsl_renderchain_bind_prev (TYPE_5__*,int /*<<< orphan*/ ,struct shader_pass*) ; 
 int /*<<< orphan*/  d3d9_renderchain_add_lut_internal (TYPE_5__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  d3d9_renderchain_unbind_all (TYPE_7__*) ; 
 int /*<<< orphan*/  d3d9_set_sampler_magfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_minfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_stream_source (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d3d9_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_vertex_declaration (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d_translate_filter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hlsl_d3d9_renderchain_render_pass(
      hlsl_renderchain_t *chain,
      struct shader_pass *pass,
      unsigned pass_index)
{
   unsigned i;

   d3d9_hlsl_bind_program(pass, chain->chain.dev);

   d3d9_set_texture(chain->chain.dev, 0, pass->tex);
   d3d9_set_sampler_minfilter(chain->chain.dev, 0,
         d3d_translate_filter(pass->info.pass->filter));
   d3d9_set_sampler_magfilter(chain->chain.dev, 0,
         d3d_translate_filter(pass->info.pass->filter));

   d3d9_set_vertex_declaration(chain->chain.dev, pass->vertex_decl);
   for (i = 0; i < 4; i++)
      d3d9_set_stream_source(chain->chain.dev, i,
            pass->vertex_buf, 0,
            sizeof(struct D3D9Vertex));

#if 0
   /* Set orig texture. */
   d3d9_hlsl_renderchain_bind_orig(chain, chain->dev, pass);

   /* Set prev textures. */
   d3d9_hlsl_renderchain_bind_prev(chain, chain->dev, pass);

   /* Set lookup textures */
   for (i = 0; i < chain->luts->count; i++)
   {
      CGparameter vparam;
      CGparameter fparam = d3d9_hlsl_get_constant_by_name(
            pass->fprg, chain->luts->data[i].id);
      int bound_index    = -1;

      if (fparam)
      {
         unsigned index  = cgGetParameterResourceIndex(fparam);
         bound_index     = index;

         d3d9_renderchain_add_lut_internal(chain, index, i);
      }

      vparam = d3d9_hlsl_get_constant_by_name(pass->vprg,
            chain->luts->data[i].id);

      if (vparam)
      {
         unsigned index = cgGetParameterResourceIndex(vparam);
         if (index != (unsigned)bound_index)
            d3d9_renderchain_add_lut_internal(chain, index, i);
      }
   }

   /* We only bother binding passes which are two indices behind. */
   if (pass_index >= 3)
      d3d9_hlsl_renderchain_bind_pass(chain, chain->chain.dev, pass, pass_index);

#endif

   d3d9_draw_primitive(chain->chain.dev, D3DPT_TRIANGLESTRIP, 0, 2);

   /* So we don't render with linear filter into render targets,
    * which apparently looked odd (too blurry). */
   d3d9_set_sampler_minfilter(chain->chain.dev, 0, D3DTEXF_POINT);
   d3d9_set_sampler_magfilter(chain->chain.dev, 0, D3DTEXF_POINT);

   d3d9_renderchain_unbind_all(&chain->chain);
}