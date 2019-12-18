#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int video_smooth; } ;
struct TYPE_9__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_10__ {int /*<<< orphan*/  mvp_rotate; int /*<<< orphan*/  dev; int /*<<< orphan*/  final_viewport; } ;
typedef  TYPE_3__ d3d8_video_t ;
struct TYPE_11__ {int /*<<< orphan*/  vertex_buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  tex; } ;
typedef  TYPE_4__ d3d8_renderchain_t ;
typedef  int /*<<< orphan*/  Vertex ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE8 ;

/* Variables and functions */
 int D3DFVF_DIFFUSE ; 
 int D3DFVF_TEX1 ; 
 int D3DFVF_XYZ ; 
 int /*<<< orphan*/  D3DPT_TRIANGLESTRIP ; 
 int /*<<< orphan*/  D3DTEXF_LINEAR ; 
 int /*<<< orphan*/  D3DTEXF_POINT ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  d3d8_draw_primitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d3d8_set_mvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d8_set_sampler_magfilter (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_set_sampler_minfilter (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_set_stream_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d3d8_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_set_vertex_shader (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d8_set_viewports (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3d8_renderchain_render_pass(
      d3d8_video_t *d3d, LPDIRECT3DDEVICE8 d3dr,
      d3d8_renderchain_t *chain,
      unsigned pass_index,
      unsigned rotation)
{
   settings_t *settings      = config_get_ptr();
   bool video_smooth         = settings->bools.video_smooth;

   d3d8_set_texture(d3dr, 0, chain->tex);
   d3d8_set_sampler_magfilter(d3dr, pass_index, video_smooth ?
         D3DTEXF_LINEAR : D3DTEXF_POINT);
   d3d8_set_sampler_minfilter(d3dr, pass_index, video_smooth ?
         D3DTEXF_LINEAR : D3DTEXF_POINT);

   d3d8_set_viewports(chain->dev, &d3d->final_viewport);
   d3d8_set_vertex_shader(d3dr,
         D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE,
         NULL);
   d3d8_set_stream_source(d3dr, 0, chain->vertex_buf, 0, sizeof(Vertex));
   d3d8_set_mvp(d3d->dev, &d3d->mvp_rotate);
   d3d8_draw_primitive(d3dr, D3DPT_TRIANGLESTRIP, 0, 2);
}