#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int invalid_swapchain; } ;
struct TYPE_7__ {int need_new_swapchain; TYPE_1__ context; int /*<<< orphan*/  created_new_swapchain; int /*<<< orphan*/  swapchain; } ;
struct TYPE_6__ {TYPE_3__ vk; int /*<<< orphan*/  g_interval; } ;
typedef  TYPE_2__ gfx_ctx_x_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  VK_NULL_HANDLE ; 
 int /*<<< orphan*/  vulkan_acquire_next_image (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_create_swapchain (TYPE_3__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int x_api ; 

__attribute__((used)) static bool gfx_ctx_x_set_resize(void *data,
      unsigned width, unsigned height)
{
   (void)data;
   (void)width;
   (void)height;

   switch (x_api)
   {
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         {
            gfx_ctx_x_data_t *x = (gfx_ctx_x_data_t*)data;

            /* FIXME/TODO - threading error here */

            if (!vulkan_create_swapchain(&x->vk, width, height, x->g_interval))
            {
               RARCH_ERR("[X/Vulkan]: Failed to update swapchain.\n");
               x->vk.swapchain = VK_NULL_HANDLE;
               return false;
            }

            if (x->vk.created_new_swapchain)
               vulkan_acquire_next_image(&x->vk);
            x->vk.context.invalid_swapchain = true;
            x->vk.need_new_swapchain        = false;
         }
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }
   return true;
}