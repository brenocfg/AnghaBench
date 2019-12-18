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
struct TYPE_2__ {int need_new_swapchain; int /*<<< orphan*/  swapchain; } ;

/* Variables and functions */
#define  GFX_CTX_NONE 130 
#define  GFX_CTX_OPENGL_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  RARCH_LOG (char*,int) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  p_swap_interval (int) ; 
 int win32_api ; 
 int /*<<< orphan*/  win32_hrc ; 
 int win32_interval ; 
 TYPE_1__ win32_vk ; 

__attribute__((used)) static void gfx_ctx_wgl_swap_interval(void *data, int interval)
{
   (void)data;

   switch (win32_api)
   {
      case GFX_CTX_OPENGL_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         win32_interval = interval;
         if (!win32_hrc)
            return;
         if (!p_swap_interval)
            return;

         RARCH_LOG("[WGL]: wglSwapInterval(%i)\n", win32_interval);
         if (!p_swap_interval(win32_interval))
            RARCH_WARN("[WGL]: wglSwapInterval() failed.\n");
#endif
         break;

      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         if (win32_interval != interval)
         {
            win32_interval = interval;
            if (win32_vk.swapchain)
               win32_vk.need_new_swapchain = true;
         }
#endif
         break;

      case GFX_CTX_NONE:
      default:
         win32_interval = interval;
         break;
   }
}