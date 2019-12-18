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
struct TYPE_10__ {int /*<<< orphan*/ * vbo; int /*<<< orphan*/  shader_font; int /*<<< orphan*/  shader; } ;
struct TYPE_9__ {int /*<<< orphan*/ * vbo; int /*<<< orphan*/  texture; } ;
struct TYPE_8__ {int /*<<< orphan*/ * vbo; int /*<<< orphan*/ * ubo; int /*<<< orphan*/ * texture; } ;
struct TYPE_11__ {int /*<<< orphan*/ * device; int /*<<< orphan*/  context; int /*<<< orphan*/ * swapChain; int /*<<< orphan*/ * renderTargetView; int /*<<< orphan*/ * state; int /*<<< orphan*/ *** samplers; int /*<<< orphan*/ * blend_disable; int /*<<< orphan*/ * blend_enable; int /*<<< orphan*/ * ubo; int /*<<< orphan*/ * blend_pipeline; int /*<<< orphan*/ * menu_pipeline_vbo; int /*<<< orphan*/ * shaders; TYPE_3__ sprites; TYPE_2__ menu; TYPE_1__ frame; } ;
typedef  TYPE_4__ d3d10_video_t ;

/* Variables and functions */
 unsigned int D3D10_MAX_GPU_COUNT ; 
 unsigned int GFX_MAX_SHADERS ; 
 size_t RARCH_FILTER_LINEAR ; 
 size_t RARCH_FILTER_NEAREST ; 
 unsigned int RARCH_WRAP_MAX ; 
 int /*<<< orphan*/  Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cached_context ; 
 int /*<<< orphan*/ * cached_device_d3d10 ; 
 int /*<<< orphan*/ ** d3d10_adapters ; 
 int /*<<< orphan*/  d3d10_free_overlays (TYPE_4__*) ; 
 int /*<<< orphan*/  d3d10_free_shader_preset (TYPE_4__*) ; 
 int /*<<< orphan*/  d3d10_release_shader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d10_release_texture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  font_driver_free_osd () ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ video_driver_is_video_cache_context () ; 
 int /*<<< orphan*/  win32_destroy_window () ; 
 int /*<<< orphan*/  win32_monitor_from_window () ; 

__attribute__((used)) static void d3d10_gfx_free(void* data)
{
   unsigned       i;
   d3d10_video_t* d3d10 = (d3d10_video_t*)data;

   if (!d3d10)
      return;

#ifdef HAVE_OVERLAY
   d3d10_free_overlays(d3d10);
#endif

   d3d10_free_shader_preset(d3d10);

   d3d10_release_texture(&d3d10->frame.texture[0]);
   Release(d3d10->frame.ubo);
   Release(d3d10->frame.vbo);

   d3d10_release_texture(&d3d10->menu.texture);
   Release(d3d10->menu.vbo);

   d3d10_release_shader(&d3d10->sprites.shader);
   d3d10_release_shader(&d3d10->sprites.shader_font);
   Release(d3d10->sprites.vbo);

   for (i = 0; i < GFX_MAX_SHADERS; i++)
      d3d10_release_shader(&d3d10->shaders[i]);

   Release(d3d10->menu_pipeline_vbo);
   Release(d3d10->blend_pipeline);

   Release(d3d10->ubo);

   Release(d3d10->blend_enable);
   Release(d3d10->blend_disable);

   for (i = 0; i < RARCH_WRAP_MAX; i++)
   {
      Release(d3d10->samplers[RARCH_FILTER_LINEAR][i]);
      Release(d3d10->samplers[RARCH_FILTER_NEAREST][i]);
   }

   Release(d3d10->state);
   Release(d3d10->renderTargetView);
   Release(d3d10->swapChain);

   font_driver_free_osd();

#if 0
   if (video_driver_is_video_cache_context())
   {
      cached_device_d3d10 = d3d10->device;
      cached_context = d3d10->context;
   }
   else
#endif
   {
      Release(d3d10->device);
   }

   for (i = 0; i < D3D10_MAX_GPU_COUNT; i++)
   {
      if (d3d10_adapters[i])
      {
         Release(d3d10_adapters[i]);
         d3d10_adapters[i] = NULL;
      }
   }

#ifdef HAVE_MONITOR
   win32_monitor_from_window();
#endif
#ifdef HAVE_WINDOW
   win32_destroy_window();
#endif
   free(d3d10);
}