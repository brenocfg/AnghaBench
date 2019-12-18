#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int invalid_swapchain; } ;
struct TYPE_6__ {int need_new_swapchain; TYPE_1__ context; int /*<<< orphan*/  created_new_swapchain; } ;

/* Variables and functions */
#define  GFX_CTX_NONE 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  vulkan_acquire_next_image (TYPE_2__*) ; 
 int /*<<< orphan*/  vulkan_create_swapchain (TYPE_2__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int win32_api ; 
 int /*<<< orphan*/  win32_interval ; 
 TYPE_2__ win32_vk ; 

__attribute__((used)) static bool gfx_ctx_wgl_set_resize(void *data,
      unsigned width, unsigned height)
{
   (void)data;
   (void)width;
   (void)height;

   switch (win32_api)
   {
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         if (!vulkan_create_swapchain(&win32_vk, width, height, win32_interval))
         {
            RARCH_ERR("[Win32/Vulkan]: Failed to update swapchain.\n");
            return false;
         }

         if (win32_vk.created_new_swapchain)
            vulkan_acquire_next_image(&win32_vk);
         win32_vk.context.invalid_swapchain = true;
         win32_vk.need_new_swapchain        = false;
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }

   return false;
}