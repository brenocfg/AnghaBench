#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* scaler_type; void* out_fmt; int /*<<< orphan*/  in_fmt; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  in_height; int /*<<< orphan*/  in_width; } ;
struct TYPE_11__ {int streamed; TYPE_7__ scaler_rgb; TYPE_7__ scaler_bgr; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {TYPE_3__ readback; TYPE_2__ vp; } ;
typedef  TYPE_4__ vk_t ;
struct TYPE_9__ {scalar_t__ video_gpu_record; } ;
struct TYPE_13__ {TYPE_1__ bools; } ;
typedef  TYPE_5__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  SCALER_FMT_ABGR8888 ; 
 int /*<<< orphan*/  SCALER_FMT_ARGB8888 ; 
 void* SCALER_FMT_BGR24 ; 
 void* SCALER_TYPE_POINT ; 
 TYPE_5__* config_get_ptr () ; 
 int recording_is_enabled () ; 
 int /*<<< orphan*/  scaler_ctx_gen_filter (TYPE_7__*) ; 

__attribute__((used)) static void vulkan_init_readback(vk_t *vk)
{
   /* Only bother with this if we're doing GPU recording.
    * Check recording_is_enabled() and not
    * driver.recording_data, because recording is
    * not initialized yet.
    */
   settings_t *settings    = config_get_ptr();
   bool recording_enabled = recording_is_enabled();
   vk->readback.streamed   = settings->bools.video_gpu_record && recording_enabled;

   if (!vk->readback.streamed)
      return;

   vk->readback.scaler_bgr.in_width    = vk->vp.width;
   vk->readback.scaler_bgr.in_height   = vk->vp.height;
   vk->readback.scaler_bgr.out_width   = vk->vp.width;
   vk->readback.scaler_bgr.out_height  = vk->vp.height;
   vk->readback.scaler_bgr.in_fmt      = SCALER_FMT_ARGB8888;
   vk->readback.scaler_bgr.out_fmt     = SCALER_FMT_BGR24;
   vk->readback.scaler_bgr.scaler_type = SCALER_TYPE_POINT;

   vk->readback.scaler_rgb.in_width    = vk->vp.width;
   vk->readback.scaler_rgb.in_height   = vk->vp.height;
   vk->readback.scaler_rgb.out_width   = vk->vp.width;
   vk->readback.scaler_rgb.out_height  = vk->vp.height;
   vk->readback.scaler_rgb.in_fmt      = SCALER_FMT_ABGR8888;
   vk->readback.scaler_rgb.out_fmt     = SCALER_FMT_BGR24;
   vk->readback.scaler_rgb.scaler_type = SCALER_TYPE_POINT;

   if (!scaler_ctx_gen_filter(&vk->readback.scaler_bgr))
   {
      vk->readback.streamed = false;
      RARCH_ERR("[Vulkan]: Failed to initialize scaler context.\n");
   }

   if (!scaler_ctx_gen_filter(&vk->readback.scaler_rgb))
   {
      vk->readback.streamed = false;
      RARCH_ERR("[Vulkan]: Failed to initialize scaler context.\n");
   }
}