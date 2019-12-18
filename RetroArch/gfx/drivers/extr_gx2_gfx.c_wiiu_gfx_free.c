#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  image; } ;
struct TYPE_15__ {TYPE_8__ surface; } ;
struct TYPE_22__ {int /*<<< orphan*/  v; } ;
struct TYPE_21__ {int /*<<< orphan*/  v; } ;
struct TYPE_18__ {int /*<<< orphan*/  image; } ;
struct TYPE_19__ {TYPE_3__ surface; } ;
struct TYPE_20__ {int /*<<< orphan*/  v; TYPE_4__ texture; } ;
struct TYPE_16__ {int /*<<< orphan*/  image; } ;
struct TYPE_17__ {TYPE_1__ surface; } ;
struct TYPE_24__ {int /*<<< orphan*/  drc_scan_buffer; int /*<<< orphan*/  tv_scan_buffer; int /*<<< orphan*/  output_ring_buffer; int /*<<< orphan*/  input_ring_buffer; int /*<<< orphan*/  ubo_mvp; int /*<<< orphan*/  ubo_tex; int /*<<< orphan*/  ubo_vp; TYPE_13__ color_buffer; int /*<<< orphan*/  menu_shader_ubo; int /*<<< orphan*/  menu_shader_vbo; TYPE_7__ vertex_cache_tex; TYPE_6__ vertex_cache; TYPE_5__ menu; int /*<<< orphan*/  v; TYPE_2__ texture; int /*<<< orphan*/  cmd_buffer; int /*<<< orphan*/  ctx_state; } ;
typedef  TYPE_9__ wiiu_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  GX2ClearColor (TYPE_13__*,float,float,float,float) ; 
 int /*<<< orphan*/  GX2CopyColorBufferToScanBuffer (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2DestroyShader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GX2DrawDone () ; 
 int /*<<< orphan*/  GX2Flush () ; 
 int /*<<< orphan*/  GX2SetDRCEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2SetTVEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2Shutdown () ; 
 int /*<<< orphan*/  GX2SwapScanBuffers () ; 
 int /*<<< orphan*/  GX2WaitForVsync () ; 
 int /*<<< orphan*/  GX2_DISABLE ; 
 int /*<<< orphan*/  GX2_SCAN_TARGET_DRC ; 
 int /*<<< orphan*/  GX2_SCAN_TARGET_TV ; 
 int /*<<< orphan*/  MEM1_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM2_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMBucket_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bokeh_shader ; 
 int /*<<< orphan*/  frame_shader ; 
 int /*<<< orphan*/  free (TYPE_9__*) ; 
 int /*<<< orphan*/  gx2_free_overlay (TYPE_9__*) ; 
 int /*<<< orphan*/  ribbon_shader ; 
 int /*<<< orphan*/  ribbon_simple_shader ; 
 int /*<<< orphan*/  snow_shader ; 
 int /*<<< orphan*/  snow_simple_shader ; 
 int /*<<< orphan*/  snowflake_shader ; 
 int /*<<< orphan*/  sprite_shader ; 
 int /*<<< orphan*/  tex_shader ; 
 int /*<<< orphan*/  wiiu_free_shader_preset (TYPE_9__*) ; 

__attribute__((used)) static void wiiu_gfx_free(void *data)
{
   wiiu_video_t *wiiu = (wiiu_video_t *) data;

   if (!wiiu)
      return;

   /* clear leftover image */
   GX2ClearColor(&wiiu->color_buffer, 0.0f, 0.0f, 0.0f, 1.0f);
   GX2CopyColorBufferToScanBuffer(&wiiu->color_buffer, GX2_SCAN_TARGET_DRC);
   GX2CopyColorBufferToScanBuffer(&wiiu->color_buffer, GX2_SCAN_TARGET_TV);

   GX2SwapScanBuffers();
   GX2Flush();
   GX2DrawDone();
   GX2WaitForVsync();
   GX2Shutdown();

   GX2SetTVEnable(GX2_DISABLE);
   GX2SetDRCEnable(GX2_DISABLE);

   GX2DestroyShader(&frame_shader);
   GX2DestroyShader(&tex_shader);
   GX2DestroyShader(&sprite_shader);
   GX2DestroyShader(&ribbon_simple_shader);
   GX2DestroyShader(&ribbon_shader);
   GX2DestroyShader(&bokeh_shader);
   GX2DestroyShader(&snow_shader);
   GX2DestroyShader(&snow_simple_shader);
   GX2DestroyShader(&snowflake_shader);

   wiiu_free_shader_preset(wiiu);

#ifdef HAVE_OVERLAY
   gx2_free_overlay(wiiu);
#endif

   MEM2_free(wiiu->ctx_state);
   MEM2_free(wiiu->cmd_buffer);
   MEM2_free(wiiu->texture.surface.image);
   MEM2_free(wiiu->menu.texture.surface.image);
   MEM2_free(wiiu->v);
   MEM2_free(wiiu->menu.v);
   MEM2_free(wiiu->vertex_cache.v);
   MEM2_free(wiiu->vertex_cache_tex.v);
   MEM2_free(wiiu->menu_shader_vbo);
   MEM2_free(wiiu->menu_shader_ubo);

   MEM1_free(wiiu->color_buffer.surface.image);
   MEM1_free(wiiu->ubo_vp);
   MEM1_free(wiiu->ubo_tex);
   MEM1_free(wiiu->ubo_mvp);
   MEM1_free(wiiu->input_ring_buffer);
   MEM1_free(wiiu->output_ring_buffer);

   MEMBucket_free(wiiu->tv_scan_buffer);
   MEMBucket_free(wiiu->drc_scan_buffer);

   free(wiiu);
}