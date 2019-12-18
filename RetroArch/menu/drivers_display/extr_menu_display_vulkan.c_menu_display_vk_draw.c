#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  nearest; int /*<<< orphan*/  linear; int /*<<< orphan*/  mipmap_linear; } ;
struct vk_texture {int /*<<< orphan*/  default_smooth; int /*<<< orphan*/  mipmap; } ;
struct TYPE_22__ {int /*<<< orphan*/  blend; int /*<<< orphan*/ * pipelines; struct vk_texture blank_texture; } ;
struct TYPE_18__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_25__ {TYPE_6__ samplers; TYPE_5__ display; TYPE_2__* chain; int /*<<< orphan*/  context; TYPE_1__ tracker; } ;
typedef  TYPE_8__ vk_t ;
struct TYPE_26__ {scalar_t__ userdata; } ;
typedef  TYPE_9__ video_frame_info_t ;
struct TYPE_20__ {int /*<<< orphan*/  a; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct vk_vertex {float y; TYPE_3__ color; int /*<<< orphan*/  tex_y; int /*<<< orphan*/  tex_x; int /*<<< orphan*/  x; } ;
struct vk_draw_triangles {int uniform_size; unsigned int vertices; struct vk_buffer_range* vbo; int /*<<< orphan*/  uniform; int /*<<< orphan*/  sampler; struct vk_texture* texture; int /*<<< orphan*/  pipeline; } ;
struct vk_buffer_range {scalar_t__ data; } ;
struct TYPE_21__ {int id; int backend_data_size; int /*<<< orphan*/  backend_data; } ;
struct TYPE_17__ {TYPE_7__* coords; int /*<<< orphan*/  matrix_data; int /*<<< orphan*/  prim_type; TYPE_4__ pipeline; scalar_t__ texture; } ;
typedef  TYPE_10__ menu_display_ctx_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;
struct TYPE_24__ {float* vertex; float* tex_coord; float* color; int vertices; void* lut_tex_coord; } ;
struct TYPE_19__ {int /*<<< orphan*/  vbo; } ;

/* Variables and functions */
#define  VIDEO_SHADER_MENU 132 
#define  VIDEO_SHADER_MENU_2 131 
#define  VIDEO_SHADER_MENU_3 130 
#define  VIDEO_SHADER_MENU_4 129 
#define  VIDEO_SHADER_MENU_5 128 
 int /*<<< orphan*/  VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VULKAN_DIRTY_DYNAMIC_BIT ; 
 float* menu_display_vk_get_default_color () ; 
 int /*<<< orphan*/  menu_display_vk_get_default_mvp (TYPE_9__*) ; 
 void* menu_display_vk_get_default_tex_coords () ; 
 float* menu_display_vk_get_default_vertices () ; 
 int /*<<< orphan*/  menu_display_vk_viewport (TYPE_10__*,TYPE_9__*) ; 
 size_t to_display_pipeline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t to_menu_pipeline (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vulkan_buffer_chain_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct vk_buffer_range*) ; 
 int /*<<< orphan*/  vulkan_draw_triangles (TYPE_8__*,struct vk_draw_triangles*) ; 

__attribute__((used)) static void menu_display_vk_draw(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   unsigned i;
   struct vk_buffer_range range;
   struct vk_texture *texture    = NULL;
   const float *vertex           = NULL;
   const float *tex_coord        = NULL;
   const float *color            = NULL;
   struct vk_vertex *pv          = NULL;
   vk_t *vk                      = (vk_t*)video_info->userdata;

   if (!vk || !draw)
      return;

   texture            = (struct vk_texture*)draw->texture;
   vertex             = draw->coords->vertex;
   tex_coord          = draw->coords->tex_coord;
   color              = draw->coords->color;

   if (!vertex)
      vertex          = menu_display_vk_get_default_vertices();
   if (!tex_coord)
      tex_coord       = menu_display_vk_get_default_tex_coords();
   if (!draw->coords->lut_tex_coord)
      draw->coords->lut_tex_coord = menu_display_vk_get_default_tex_coords();
   if (!texture)
      texture         = &vk->display.blank_texture;
   if (!color)
      color           = menu_display_vk_get_default_color();

   menu_display_vk_viewport(draw, video_info);

   vk->tracker.dirty |= VULKAN_DIRTY_DYNAMIC_BIT;

   /* Bake interleaved VBO. Kinda ugly, we should probably try to move to
    * an interleaved model to begin with ... */
   if (!vulkan_buffer_chain_alloc(vk->context, &vk->chain->vbo,
         draw->coords->vertices * sizeof(struct vk_vertex), &range))
      return;

   pv = (struct vk_vertex*)range.data;
   for (i = 0; i < draw->coords->vertices; i++, pv++)
   {
      pv->x       = *vertex++;
      /* Y-flip. Vulkan is top-left clip space */
      pv->y       = 1.0f - (*vertex++);
      pv->tex_x   = *tex_coord++;
      pv->tex_y   = *tex_coord++;
      pv->color.r = *color++;
      pv->color.g = *color++;
      pv->color.b = *color++;
      pv->color.a = *color++;
   }

   switch (draw->pipeline.id)
   {
#ifdef HAVE_SHADERPIPELINE
      case VIDEO_SHADER_MENU:
      case VIDEO_SHADER_MENU_2:
      case VIDEO_SHADER_MENU_3:
      case VIDEO_SHADER_MENU_4:
      case VIDEO_SHADER_MENU_5:
      {
         struct vk_draw_triangles call;

         call.pipeline     = vk->display.pipelines[
               to_menu_pipeline(draw->prim_type, draw->pipeline.id)];
         call.texture      = NULL;
         call.sampler      = VK_NULL_HANDLE;
         call.uniform      = draw->pipeline.backend_data;
         call.uniform_size = draw->pipeline.backend_data_size;
         call.vbo          = &range;
         call.vertices     = draw->coords->vertices;

         vulkan_draw_triangles(vk, &call);
         break;
      }

         break;
#endif

      default:
      {
         struct vk_draw_triangles call;

         call.pipeline     = vk->display.pipelines[
               to_display_pipeline(draw->prim_type, vk->display.blend)];
         call.texture      = texture;
         call.sampler      = texture->mipmap ?
            vk->samplers.mipmap_linear :
            (texture->default_smooth ? vk->samplers.linear
             : vk->samplers.nearest);
         call.uniform      = draw->matrix_data
            ? draw->matrix_data : menu_display_vk_get_default_mvp(video_info);
         call.uniform_size = sizeof(math_matrix_4x4);
         call.vbo          = &range;
         call.vertices     = draw->coords->vertices;

         vulkan_draw_triangles(vk, &call);
         break;
      }
   }
}