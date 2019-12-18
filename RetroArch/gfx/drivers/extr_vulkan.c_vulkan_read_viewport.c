#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int height; int width; } ;
struct scaler_ctx {int out_stride; int /*<<< orphan*/  in_stride; } ;
struct TYPE_6__ {int pending; struct scaler_ctx scaler_bgr; struct scaler_ctx scaler_rgb; scalar_t__ streamed; struct vk_texture* staging; } ;
struct TYPE_9__ {TYPE_3__* context; TYPE_2__ vp; TYPE_1__ readback; } ;
typedef  TYPE_4__ vk_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct vk_texture {scalar_t__ memory; int /*<<< orphan*/  stride; scalar_t__ mapped; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {size_t current_swapchain_index; int swapchain_format; int /*<<< orphan*/  device; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
#define  VK_FORMAT_A8B8G8R8_UNORM_PACK32 130 
#define  VK_FORMAT_B8G8R8A8_UNORM 129 
#define  VK_FORMAT_R8G8B8A8_UNORM 128 
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  scaler_ctx_scale_direct (struct scaler_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_cached_frame () ; 
 int /*<<< orphan*/  vkMapMemory (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  vkQueueWaitIdle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkUnmapMemory (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vulkan_destroy_texture (int /*<<< orphan*/ ,struct vk_texture*) ; 
 int /*<<< orphan*/  vulkan_map_persistent_texture (int /*<<< orphan*/ ,struct vk_texture*) ; 
 int /*<<< orphan*/  vulkan_sync_texture_to_cpu (TYPE_4__*,struct vk_texture*) ; 

__attribute__((used)) static bool vulkan_read_viewport(void *data, uint8_t *buffer, bool is_idle)
{
   struct vk_texture *staging       = NULL;
   vk_t *vk                         = (vk_t*)data;

   if (!vk)
      return false;

   staging = &vk->readback.staging[vk->context->current_swapchain_index];

   if (vk->readback.streamed)
   {
      const uint8_t *src     = NULL;
      struct scaler_ctx *ctx = NULL;

      switch (vk->context->swapchain_format)
      {
         case VK_FORMAT_R8G8B8A8_UNORM:
         case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
            ctx = &vk->readback.scaler_rgb;
            break;

         case VK_FORMAT_B8G8R8A8_UNORM:
            ctx = &vk->readback.scaler_bgr;
            break;

         default:
            RARCH_ERR("[Vulkan]: Unexpected swapchain format. Cannot readback.\n");
            break;
      }

      if (ctx)
      {
         if (staging->memory == VK_NULL_HANDLE)
            return false;

         buffer += 3 * (vk->vp.height - 1) * vk->vp.width;
         vkMapMemory(vk->context->device, staging->memory,
               staging->offset, staging->size, 0, (void**)&src);

         vulkan_sync_texture_to_cpu(vk, staging);

         ctx->in_stride  = staging->stride;
         ctx->out_stride = -(int)vk->vp.width * 3;
         scaler_ctx_scale_direct(ctx, buffer, src);

         vkUnmapMemory(vk->context->device, staging->memory);
      }
   }
   else
   {
      /* Synchronous path only for now. */
      /* TODO: How will we deal with format conversion?
       * For now, take the simplest route and use image blitting
       * with conversion. */

      vk->readback.pending = true;

      if (!is_idle)
         video_driver_cached_frame();

#ifdef HAVE_THREADS
      slock_lock(vk->context->queue_lock);
#endif
      vkQueueWaitIdle(vk->context->queue);
#ifdef HAVE_THREADS
      slock_unlock(vk->context->queue_lock);
#endif

      if (!staging->mapped)
         vulkan_map_persistent_texture(
               vk->context->device, staging);

      vulkan_sync_texture_to_cpu(vk, staging);

      {
         unsigned x, y;
         const uint8_t *src = (const uint8_t*)staging->mapped;
         buffer += 3 * (vk->vp.height - 1) * vk->vp.width;

         switch (vk->context->swapchain_format)
         {
            case VK_FORMAT_B8G8R8A8_UNORM:
               for (y = 0; y < vk->vp.height; y++,
                     src += staging->stride, buffer -= 3 * vk->vp.width)
               {
                  for (x = 0; x < vk->vp.width; x++)
                  {
                     buffer[3 * x + 0] = src[4 * x + 0];
                     buffer[3 * x + 1] = src[4 * x + 1];
                     buffer[3 * x + 2] = src[4 * x + 2];
                  }
               }
               break;

            case VK_FORMAT_R8G8B8A8_UNORM:
            case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
               for (y = 0; y < vk->vp.height; y++,
                     src += staging->stride, buffer -= 3 * vk->vp.width)
               {
                  for (x = 0; x < vk->vp.width; x++)
                  {
                     buffer[3 * x + 2] = src[4 * x + 0];
                     buffer[3 * x + 1] = src[4 * x + 1];
                     buffer[3 * x + 0] = src[4 * x + 2];
                  }
               }
               break;

            default:
               RARCH_ERR("[Vulkan]: Unexpected swapchain format.\n");
               break;
         }
      }
      vulkan_destroy_texture(
            vk->context->device, staging);
   }
   return true;
}