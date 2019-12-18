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
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ userdata; } ;
typedef  TYPE_7__ video_frame_info_t ;
struct TYPE_23__ {int vertices; int /*<<< orphan*/  vertex; } ;
struct TYPE_29__ {TYPE_2__ coords; } ;
typedef  TYPE_8__ video_coord_array_t ;
struct TYPE_22__ {int id; } ;
struct TYPE_30__ {TYPE_4__* coords; TYPE_1__ pipeline; } ;
typedef  TYPE_9__ menu_display_ctx_draw_t ;
struct TYPE_27__ {int /*<<< orphan*/  BufferLocation; } ;
struct TYPE_26__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_19__ {float time; } ;
struct TYPE_21__ {int StrideInBytes; int SizeInBytes; int /*<<< orphan*/  BufferLocation; } ;
struct TYPE_24__ {TYPE_17__ vbo_view; } ;
struct TYPE_18__ {TYPE_6__ ubo_view; TYPE_5__ queue; int /*<<< orphan*/  ubo; TYPE_11__ ubo_values; TYPE_3__ frame; TYPE_17__ menu_pipeline_vbo_view; int /*<<< orphan*/  menu_pipeline_vbo; int /*<<< orphan*/  device; } ;
typedef  TYPE_10__ d3d12_video_t ;
typedef  TYPE_11__ d3d12_uniform_t ;
struct TYPE_25__ {int vertices; } ;
struct TYPE_20__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_12__ D3D12_RANGE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12IASetPrimitiveTopology (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D12IASetVertexBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_17__*) ; 
 int /*<<< orphan*/  D3D12Map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_12__*,void**) ; 
 int /*<<< orphan*/  D3D12SetGraphicsRootConstantBufferView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D12Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP ; 
 int /*<<< orphan*/  ROOT_ID_UBO ; 
#define  VIDEO_SHADER_MENU 133 
#define  VIDEO_SHADER_MENU_2 132 
#define  VIDEO_SHADER_MENU_3 131 
#define  VIDEO_SHADER_MENU_4 130 
#define  VIDEO_SHADER_MENU_5 129 
#define  VIDEO_SHADER_MENU_6 128 
 int /*<<< orphan*/  d3d12_create_buffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 TYPE_8__* menu_display_get_coords_array () ; 

__attribute__((used)) static void menu_display_d3d12_draw_pipeline(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   d3d12_video_t *d3d12 = (d3d12_video_t*)video_info->userdata;

   if (!d3d12 || !draw)
      return;

   switch (draw->pipeline.id)
   {
      case VIDEO_SHADER_MENU:
      case VIDEO_SHADER_MENU_2:
      {
         video_coord_array_t* ca = menu_display_get_coords_array();

         if (!d3d12->menu_pipeline_vbo)
         {
            void*       vertex_data_begin;
            D3D12_RANGE read_range = { 0, 0 };

            d3d12->menu_pipeline_vbo_view.StrideInBytes = 2 * sizeof(float);
            d3d12->menu_pipeline_vbo_view.SizeInBytes =
                  ca->coords.vertices * d3d12->menu_pipeline_vbo_view.StrideInBytes;
            d3d12->menu_pipeline_vbo_view.BufferLocation = d3d12_create_buffer(
                  d3d12->device, d3d12->menu_pipeline_vbo_view.SizeInBytes,
                  &d3d12->menu_pipeline_vbo);

            D3D12Map(d3d12->menu_pipeline_vbo, 0, &read_range, &vertex_data_begin);
            memcpy(vertex_data_begin, ca->coords.vertex, d3d12->menu_pipeline_vbo_view.SizeInBytes);
            D3D12Unmap(d3d12->menu_pipeline_vbo, 0, NULL);
         }
         D3D12IASetVertexBuffers(d3d12->queue.cmd, 0, 1, &d3d12->menu_pipeline_vbo_view);
         draw->coords->vertices = ca->coords.vertices;
         break;
      }

      case VIDEO_SHADER_MENU_3:
      case VIDEO_SHADER_MENU_4:
      case VIDEO_SHADER_MENU_5:
      case VIDEO_SHADER_MENU_6:
         D3D12IASetVertexBuffers(d3d12->queue.cmd, 0, 1, &d3d12->frame.vbo_view);
         draw->coords->vertices = 4;
         break;
      default:
         return;
   }
   D3D12IASetPrimitiveTopology(d3d12->queue.cmd, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

   d3d12->ubo_values.time += 0.01f;

   {
      D3D12_RANGE      read_range = { 0, 0 };
      d3d12_uniform_t* mapped_ubo;
      D3D12Map(d3d12->ubo, 0, &read_range, (void**)&mapped_ubo);
      *mapped_ubo = d3d12->ubo_values;
      D3D12Unmap(d3d12->ubo, 0, NULL);
   }
   D3D12SetGraphicsRootConstantBufferView(
         d3d12->queue.cmd, ROOT_ID_UBO, d3d12->ubo_view.BufferLocation);
}