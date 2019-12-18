#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  need_new_swapchain; } ;
struct TYPE_4__ {TYPE_1__ vk; } ;
typedef  TYPE_2__ gfx_ctx_x_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  x11_check_window (void*,int*,int*,unsigned int*,unsigned int*,int) ; 
 int x_api ; 

__attribute__((used)) static void gfx_ctx_x_check_window(void *data, bool *quit,
      bool *resize, unsigned *width, unsigned *height,
      bool is_shutdown)
{
   x11_check_window(data, quit, resize, width, height,
         is_shutdown);

   switch (x_api)
   {
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         {
            gfx_ctx_x_data_t *x = (gfx_ctx_x_data_t*)data;
            if (x->vk.need_new_swapchain)
               *resize = true;
         }
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }
}