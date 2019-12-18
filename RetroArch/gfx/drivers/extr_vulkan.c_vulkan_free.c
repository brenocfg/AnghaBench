#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vulkan_filter_chain_t ;
struct TYPE_9__ {int /*<<< orphan*/  scaler_rgb; int /*<<< orphan*/  scaler_bgr; } ;
struct TYPE_11__ {TYPE_1__ readback; scalar_t__ filter_chain; TYPE_2__* context; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_10__ {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  font_driver_free_osd () ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  scaler_ctx_gen_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_context_driver_free () ; 
 int /*<<< orphan*/  vkQueueWaitIdle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_deinit_menu (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_deinit_resources (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_deinit_static_resources (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_filter_chain_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_overlay_free (TYPE_3__*) ; 

__attribute__((used)) static void vulkan_free(void *data)
{
   vk_t *vk = (vk_t*)data;
   if (!vk)
      return;

   if (vk->context && vk->context->device)
   {
#ifdef HAVE_THREADS
      slock_lock(vk->context->queue_lock);
#endif
      vkQueueWaitIdle(vk->context->queue);
#ifdef HAVE_THREADS
      slock_unlock(vk->context->queue_lock);
#endif
      vulkan_deinit_resources(vk);

      /* No need to init this since textures are create on-demand. */
      vulkan_deinit_menu(vk);

      font_driver_free_osd();

      vulkan_deinit_static_resources(vk);
#ifdef HAVE_OVERLAY
      vulkan_overlay_free(vk);
#endif

      if (vk->filter_chain)
         vulkan_filter_chain_free((vulkan_filter_chain_t*)vk->filter_chain);

      video_context_driver_free();
   }

   scaler_ctx_gen_reset(&vk->readback.scaler_bgr);
   scaler_ctx_gen_reset(&vk->readback.scaler_rgb);
   free(vk);
}