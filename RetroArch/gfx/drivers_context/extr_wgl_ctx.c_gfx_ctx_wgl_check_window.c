#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  need_new_swapchain; } ;

/* Variables and functions */
#define  GFX_CTX_NONE 129 
#define  GFX_CTX_VULKAN_API 128 
 int win32_api ; 
 int /*<<< orphan*/  win32_check_window (int*,int*,unsigned int*,unsigned int*) ; 
 TYPE_1__ win32_vk ; 

__attribute__((used)) static void gfx_ctx_wgl_check_window(void *data, bool *quit,
      bool *resize, unsigned *width, unsigned *height,
      bool is_shutdown)
{
   win32_check_window(quit, resize, width, height);

   switch (win32_api)
   {
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         if (win32_vk.need_new_swapchain)
            *resize = true;
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }
}