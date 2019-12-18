#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ userdata; } ;
typedef  TYPE_5__ video_frame_info_t ;
struct TYPE_23__ {int vertices; int /*<<< orphan*/  vertex; } ;
struct TYPE_27__ {TYPE_2__ coords; } ;
typedef  TYPE_6__ video_coord_array_t ;
struct TYPE_22__ {int id; } ;
struct TYPE_28__ {TYPE_4__* coords; TYPE_1__ pipeline; } ;
typedef  TYPE_7__ menu_display_ctx_draw_t ;
struct TYPE_30__ {float time; } ;
struct TYPE_24__ {int /*<<< orphan*/  vbo; } ;
struct TYPE_29__ {int /*<<< orphan*/  ubo; int /*<<< orphan*/  context; TYPE_9__ ubo_values; TYPE_3__ frame; int /*<<< orphan*/  blend_pipeline; int /*<<< orphan*/  menu_pipeline_vbo; int /*<<< orphan*/  device; } ;
typedef  TYPE_8__ d3d11_video_t ;
typedef  int /*<<< orphan*/  d3d11_vertex_t ;
typedef  TYPE_9__ d3d11_uniform_t ;
struct TYPE_25__ {int vertices; } ;
struct TYPE_21__ {int ByteWidth; int /*<<< orphan*/  BindFlags; int /*<<< orphan*/  Usage; int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {scalar_t__ pData; } ;
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_10__ D3D11_SUBRESOURCE_DATA ;
typedef  TYPE_11__ D3D11_MAPPED_SUBRESOURCE ;
typedef  TYPE_12__ D3D11_BUFFER_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11CreateBuffer (int /*<<< orphan*/ ,TYPE_12__*,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11MapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  D3D11SetBlendState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D11SetPrimitiveTopology (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D11SetVertexBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D11UnmapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D11_BIND_VERTEX_BUFFER ; 
 int /*<<< orphan*/  D3D11_DEFAULT_SAMPLE_MASK ; 
 int /*<<< orphan*/  D3D11_MAP_WRITE_DISCARD ; 
 int /*<<< orphan*/  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP ; 
 int /*<<< orphan*/  D3D11_USAGE_IMMUTABLE ; 
#define  VIDEO_SHADER_MENU 133 
#define  VIDEO_SHADER_MENU_2 132 
#define  VIDEO_SHADER_MENU_3 131 
#define  VIDEO_SHADER_MENU_4 130 
#define  VIDEO_SHADER_MENU_5 129 
#define  VIDEO_SHADER_MENU_6 128 
 TYPE_6__* menu_display_get_coords_array () ; 

__attribute__((used)) static void menu_display_d3d11_draw_pipeline(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   d3d11_video_t *d3d11 = (d3d11_video_t*)video_info->userdata;

   if (!d3d11 || !draw)
      return;

   switch (draw->pipeline.id)
   {
      case VIDEO_SHADER_MENU:
      case VIDEO_SHADER_MENU_2:
      {
         video_coord_array_t* ca = menu_display_get_coords_array();

         if (!d3d11->menu_pipeline_vbo)
         {
            D3D11_BUFFER_DESC desc = { 0 };
            desc.Usage             = D3D11_USAGE_IMMUTABLE;
            desc.ByteWidth         = ca->coords.vertices * 2 * sizeof(float);
            desc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;

			{
               D3D11_SUBRESOURCE_DATA vertexData = { ca->coords.vertex };
               D3D11CreateBuffer(d3d11->device, &desc, &vertexData, &d3d11->menu_pipeline_vbo);
			}
         }
         D3D11SetVertexBuffer(d3d11->context, 0, d3d11->menu_pipeline_vbo, 2 * sizeof(float), 0);
         draw->coords->vertices = ca->coords.vertices;
         D3D11SetBlendState(d3d11->context, d3d11->blend_pipeline, NULL, D3D11_DEFAULT_SAMPLE_MASK);
         break;
      }

      case VIDEO_SHADER_MENU_3:
      case VIDEO_SHADER_MENU_4:
      case VIDEO_SHADER_MENU_5:
      case VIDEO_SHADER_MENU_6:
         D3D11SetVertexBuffer(d3d11->context, 0, d3d11->frame.vbo, sizeof(d3d11_vertex_t), 0);
         draw->coords->vertices = 4;
         break;
      default:
         return;
   }

   D3D11SetPrimitiveTopology(d3d11->context, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

   d3d11->ubo_values.time += 0.01f;

   {
      D3D11_MAPPED_SUBRESOURCE mapped_ubo;
      D3D11MapBuffer(d3d11->context, d3d11->ubo, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_ubo);
      *(d3d11_uniform_t*)mapped_ubo.pData = d3d11->ubo_values;
      D3D11UnmapBuffer(d3d11->context, d3d11->ubo, 0);
   }
}