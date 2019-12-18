#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_30__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_18__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {int current; int size; TYPE_15__* v; } ;
struct TYPE_42__ {double height; } ;
struct TYPE_43__ {TYPE_3__ surface; } ;
struct TYPE_40__ {int current; int size; TYPE_15__* v; } ;
struct TYPE_34__ {TYPE_12__ vertex_cache; int /*<<< orphan*/  ubo_tex; int /*<<< orphan*/  ubo_vp; TYPE_4__ color_buffer; TYPE_2__ vertex_cache_tex; int /*<<< orphan*/  ubo_mvp; } ;
typedef  TYPE_13__ wiiu_video_t ;
struct TYPE_35__ {scalar_t__ userdata; } ;
typedef  TYPE_14__ video_frame_info_t ;
struct TYPE_41__ {int r; int g; int b; int a; } ;
struct TYPE_45__ {float u; float v; float width; float height; } ;
struct TYPE_44__ {float x; float y; double height; int /*<<< orphan*/  width; } ;
struct TYPE_36__ {TYPE_30__ color; TYPE_6__ coord; TYPE_5__ pos; } ;
typedef  TYPE_15__ tex_shader_vertex_t ;
typedef  TYPE_15__ sprite_vertex_t ;
struct TYPE_39__ {int id; } ;
struct TYPE_37__ {float x; double y; double height; scalar_t__ texture; TYPE_7__* coords; int /*<<< orphan*/  width; TYPE_1__ pipeline; } ;
typedef  TYPE_17__ menu_display_ctx_draw_t ;
struct TYPE_48__ {TYPE_8__* samplerVars; } ;
struct TYPE_47__ {int /*<<< orphan*/  location; } ;
struct TYPE_46__ {int vertices; float* vertex; int* color; float* tex_coord; } ;
struct TYPE_32__ {TYPE_10__* uniformBlocks; } ;
struct TYPE_38__ {TYPE_11__ vs; TYPE_9__ ps; } ;
struct TYPE_31__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  GX2Texture ;

/* Variables and functions */
 TYPE_30__ COLOR_RGBA (int,int,int,int) ; 
 int /*<<< orphan*/  GX2DrawEx (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  GX2SetAttribBuffer (int /*<<< orphan*/ ,int,int,TYPE_15__*) ; 
 int /*<<< orphan*/  GX2SetBlendControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2SetPixelTexture (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2SetShader (TYPE_18__*) ; 
 int /*<<< orphan*/  GX2SetShaderMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2SetVertexUniformBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2_BLEND_COMBINE_MODE_ADD ; 
 int /*<<< orphan*/  GX2_BLEND_MODE_INV_SRC_ALPHA ; 
 int /*<<< orphan*/  GX2_BLEND_MODE_SRC_ALPHA ; 
 int /*<<< orphan*/  GX2_ENABLE ; 
 int /*<<< orphan*/  GX2_PRIMITIVE_MODE_POINTS ; 
 int /*<<< orphan*/  GX2_PRIMITIVE_MODE_QUADS ; 
 int /*<<< orphan*/  GX2_PRIMITIVE_MODE_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  GX2_RENDER_TARGET_0 ; 
 int /*<<< orphan*/  GX2_SHADER_MODE_GEOMETRY_SHADER ; 
 int /*<<< orphan*/  GX2_SHADER_MODE_UNIFORM_BLOCK ; 
#define  VIDEO_SHADER_MENU 133 
#define  VIDEO_SHADER_MENU_2 132 
#define  VIDEO_SHADER_MENU_3 131 
#define  VIDEO_SHADER_MENU_4 130 
#define  VIDEO_SHADER_MENU_5 129 
#define  VIDEO_SHADER_MENU_6 128 
 TYPE_18__ bokeh_shader ; 
 TYPE_18__ ribbon_shader ; 
 TYPE_18__ ribbon_simple_shader ; 
 TYPE_18__ snow_shader ; 
 TYPE_18__ snow_simple_shader ; 
 TYPE_18__ snowflake_shader ; 
 TYPE_18__ sprite_shader ; 
 TYPE_18__ tex_shader ; 

__attribute__((used)) static void menu_display_wiiu_draw(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   wiiu_video_t             *wiiu  = (wiiu_video_t*)video_info->userdata;

   if (!wiiu || !draw)
      return;

   if(draw->pipeline.id)
   {
      GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

      switch(draw->pipeline.id)
      {
      case VIDEO_SHADER_MENU:
         GX2SetShader(&ribbon_shader);
         break;
      case VIDEO_SHADER_MENU_2:
         GX2SetShader(&ribbon_simple_shader);
         break;
      case VIDEO_SHADER_MENU_3:
         GX2SetShader(&snow_simple_shader);
         break;
      case VIDEO_SHADER_MENU_4:
         GX2SetShader(&snow_shader);
         break;
      case VIDEO_SHADER_MENU_5:
         GX2SetShader(&bokeh_shader);
         break;
      case VIDEO_SHADER_MENU_6:
         GX2SetShader(&snowflake_shader);
         break;
      default:
         break;
      }

      switch(draw->pipeline.id)
      {
      case VIDEO_SHADER_MENU:
      case VIDEO_SHADER_MENU_2:
         GX2DrawEx(GX2_PRIMITIVE_MODE_TRIANGLE_STRIP, draw->coords->vertices, 0, 1);
         GX2SetBlendControl(GX2_RENDER_TARGET_0, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA,
                            GX2_BLEND_COMBINE_MODE_ADD,
                            GX2_ENABLE,          GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA,
                            GX2_BLEND_COMBINE_MODE_ADD);
      case VIDEO_SHADER_MENU_3:
      case VIDEO_SHADER_MENU_4:
      case VIDEO_SHADER_MENU_5:
      case VIDEO_SHADER_MENU_6:
         GX2DrawEx(GX2_PRIMITIVE_MODE_QUADS, 4, 0, 1);
         break;
      }

   }
   else if(draw->coords->vertex || draw->coords->color[0] != draw->coords->color[12])
   {
      if (wiiu->vertex_cache_tex.current + 4 > wiiu->vertex_cache_tex.size)
         return;

      tex_shader_vertex_t* v = wiiu->vertex_cache_tex.v + wiiu->vertex_cache_tex.current;

      GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);
      GX2SetShader(&tex_shader);
      GX2SetVertexUniformBlock(tex_shader.vs.uniformBlocks[0].offset,
                               tex_shader.vs.uniformBlocks[0].size,
                               wiiu->ubo_mvp);
      GX2SetAttribBuffer(0, wiiu->vertex_cache_tex.size * sizeof(*wiiu->vertex_cache_tex.v),
                         sizeof(*wiiu->vertex_cache_tex.v), wiiu->vertex_cache_tex.v);

      if(!draw->coords->vertex)
      {
         v[0].pos.x = 0.0f;
         v[0].pos.y = 1.0f;
         v[1].pos.x = 1.0f;
         v[1].pos.y = 1.0f;
         v[2].pos.x = 0.0f;
         v[2].pos.y = 0.0f;
         v[3].pos.x = 1.0f;
         v[3].pos.y = 0.0f;
      }
      else
      {
         v[0].pos.x = draw->coords->vertex[0];
         v[0].pos.y = 1.0 - draw->coords->vertex[1];
         v[1].pos.x = draw->coords->vertex[2];
         v[1].pos.y = 1.0 - draw->coords->vertex[3];
         v[2].pos.x = draw->coords->vertex[4];
         v[2].pos.y = 1.0 - draw->coords->vertex[5];
         v[3].pos.x = draw->coords->vertex[6];
         v[3].pos.y = 1.0 - draw->coords->vertex[7];
      }

      if(!draw->coords->tex_coord)
      {
         v[0].coord.u = 0.0f;
         v[0].coord.v = 1.0f;
         v[1].coord.u = 1.0f;
         v[1].coord.v = 1.0f;
         v[2].coord.u = 0.0f;
         v[2].coord.v = 0.0f;
         v[3].coord.u = 1.0f;
         v[3].coord.v = 0.0f;
      }
      else
      {
         v[0].coord.u = draw->coords->tex_coord[0];
         v[0].coord.v = draw->coords->tex_coord[1];
         v[1].coord.u = draw->coords->tex_coord[2];
         v[1].coord.v = draw->coords->tex_coord[3];
         v[2].coord.u = draw->coords->tex_coord[4];
         v[2].coord.v = draw->coords->tex_coord[5];
         v[3].coord.u = draw->coords->tex_coord[6];
         v[3].coord.v = draw->coords->tex_coord[7];
      }

      for(int i = 0; i < 4; i++)
      {
         v[i].color.r = draw->coords->color[(i << 2) + 0];
         v[i].color.g = draw->coords->color[(i << 2) + 1];
         v[i].color.b = draw->coords->color[(i << 2) + 2];
         v[i].color.a = draw->coords->color[(i << 2) + 3];
      }

      if(draw->texture)
         GX2SetPixelTexture((GX2Texture*)draw->texture, tex_shader.ps.samplerVars[0].location);

      GX2DrawEx(GX2_PRIMITIVE_MODE_TRIANGLE_STRIP, 4, wiiu->vertex_cache_tex.current, 1);
      wiiu->vertex_cache_tex.current += 4;
   }
   else
   {
      if (wiiu->vertex_cache.current + 1 > wiiu->vertex_cache.size)
         return;

      sprite_vertex_t* v = wiiu->vertex_cache.v + wiiu->vertex_cache.current;
      v->pos.x = draw->x;
      v->pos.y = wiiu->color_buffer.surface.height - draw->y - draw->height;
      v->pos.width = draw->width;
      v->pos.height = draw->height;
      v->coord.u = 0.0f;
      v->coord.v = 0.0f;
      v->coord.width = 1.0f;
      v->coord.height = 1.0f;

      v->color = COLOR_RGBA(0xFF * draw->coords->color[0], 0xFF * draw->coords->color[1],
                          0xFF * draw->coords->color[2], 0xFF * draw->coords->color[3]);

      if(draw->texture)
         GX2SetPixelTexture((GX2Texture*)draw->texture, sprite_shader.ps.samplerVars[0].location);

      GX2DrawEx(GX2_PRIMITIVE_MODE_POINTS, 1, wiiu->vertex_cache.current, 1);
      wiiu->vertex_cache.current ++;
      return;
   }

   GX2SetShaderMode(GX2_SHADER_MODE_GEOMETRY_SHADER);
   GX2SetShader(&sprite_shader);
//      GX2SetGeometryShaderInputRingBuffer(wiiu->input_ring_buffer, wiiu->input_ring_buffer_size);
//      GX2SetGeometryShaderOutputRingBuffer(wiiu->output_ring_buffer, wiiu->output_ring_buffer_size);
   GX2SetVertexUniformBlock(sprite_shader.vs.uniformBlocks[0].offset,
                            sprite_shader.vs.uniformBlocks[0].size,
                            wiiu->ubo_vp);
   GX2SetVertexUniformBlock(sprite_shader.vs.uniformBlocks[1].offset,
                            sprite_shader.vs.uniformBlocks[1].size,
                            wiiu->ubo_tex);
   GX2SetAttribBuffer(0, wiiu->vertex_cache.size * sizeof(*wiiu->vertex_cache.v),
                      sizeof(*wiiu->vertex_cache.v), wiiu->vertex_cache.v);
}