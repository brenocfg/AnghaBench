#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct unsigned_vector_list {int dummy; } ;
struct LinkInfo {TYPE_3__* pass; int /*<<< orphan*/  tex_h; int /*<<< orphan*/  tex_w; } ;
struct shader_pass {struct unsigned_vector_list* attrib_map; scalar_t__ last_height; scalar_t__ last_width; struct LinkInfo info; } ;
struct D3D9Vertex {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** tex; scalar_t__* vertex_buf; scalar_t__* last_height; scalar_t__* last_width; scalar_t__ ptr; } ;
struct TYPE_10__ {int /*<<< orphan*/  passes; int /*<<< orphan*/  dev; TYPE_1__ prev; } ;
typedef  TYPE_4__ d3d9_renderchain_t ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_9__ {TYPE_2__ source; int /*<<< orphan*/  filter; } ;
typedef  scalar_t__ LPDIRECT3DVERTEXBUFFER9 ;
typedef  int /*<<< orphan*/ * LPDIRECT3DTEXTURE9 ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;

/* Variables and functions */
 int /*<<< orphan*/  D3DPOOL_DEFAULT ; 
 int /*<<< orphan*/  D3DPOOL_MANAGED ; 
 int /*<<< orphan*/  D3DTADDRESS_BORDER ; 
 int /*<<< orphan*/  D3DUSAGE_WRITEONLY ; 
 unsigned int RETRO_PIXEL_FORMAT_RGB565 ; 
 unsigned int TEXTURES ; 
 unsigned int d3d9_get_rgb565_format () ; 
 unsigned int d3d9_get_xrgb8888_format () ; 
 int /*<<< orphan*/  d3d9_hlsl_load_program_from_file (int /*<<< orphan*/ ,struct shader_pass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_address_u (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_address_v (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_magfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_minfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ d3d9_texture_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ d3d9_vertex_buffer_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d_translate_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlsl_d3d9_renderchain_init_shader_fvf (TYPE_4__*,struct shader_pass*) ; 
 int /*<<< orphan*/  shader_pass_vector_list_append (int /*<<< orphan*/ ,struct shader_pass) ; 
 scalar_t__ unsigned_vector_list_new () ; 

__attribute__((used)) static bool hlsl_d3d9_renderchain_create_first_pass(
      LPDIRECT3DDEVICE9 dev,
      d3d9_renderchain_t *chain,
      const struct LinkInfo *info,
      unsigned _fmt)
{
   unsigned i;
   struct shader_pass pass;
   unsigned fmt =
      (_fmt == RETRO_PIXEL_FORMAT_RGB565) ?
      d3d9_get_rgb565_format() : d3d9_get_xrgb8888_format();

   pass.info        = *info;
   pass.last_width  = 0;
   pass.last_height = 0;
   pass.attrib_map  = (struct unsigned_vector_list*)
      unsigned_vector_list_new();

   chain->prev.ptr  = 0;

   for (i = 0; i < TEXTURES; i++)
   {
      chain->prev.last_width[i]  = 0;
      chain->prev.last_height[i] = 0;
      chain->prev.vertex_buf[i]  = (LPDIRECT3DVERTEXBUFFER9)
         d3d9_vertex_buffer_new(
            chain->dev, 4 * sizeof(struct D3D9Vertex),
            D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, NULL);

      if (!chain->prev.vertex_buf[i])
         return false;

      chain->prev.tex[i] = (LPDIRECT3DTEXTURE9)
         d3d9_texture_new(chain->dev, NULL,
            info->tex_w, info->tex_h, 1, 0, fmt,
            D3DPOOL_MANAGED, 0, 0, 0, NULL, NULL, false);

      if (!chain->prev.tex[i])
         return false;

      d3d9_set_texture(chain->dev, 0, chain->prev.tex[i]);
      d3d9_set_sampler_minfilter(dev, 0,
            d3d_translate_filter(info->pass->filter));
      d3d9_set_sampler_magfilter(dev, 0,
            d3d_translate_filter(info->pass->filter));
      d3d9_set_sampler_address_u(dev, 0, D3DTADDRESS_BORDER);
      d3d9_set_sampler_address_v(dev, 0, D3DTADDRESS_BORDER);
      d3d9_set_texture(chain->dev, 0, NULL);
   }

   d3d9_hlsl_load_program_from_file(chain->dev, &pass, info->pass->source.path);

   if (!hlsl_d3d9_renderchain_init_shader_fvf(chain, &pass))
      return false;
   shader_pass_vector_list_append(chain->passes, pass);
   return true;
}