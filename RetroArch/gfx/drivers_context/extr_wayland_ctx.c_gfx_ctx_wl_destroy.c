#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  queue_lock; } ;
struct TYPE_7__ {TYPE_1__ context; } ;
struct TYPE_8__ {TYPE_2__ vk; } ;
typedef  TYPE_3__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  gfx_ctx_wl_destroy_resources (TYPE_3__*) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 
 int wl_api ; 

__attribute__((used)) static void gfx_ctx_wl_destroy(void *data)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   if (!wl)
      return;

   gfx_ctx_wl_destroy_resources(wl);

   switch (wl_api)
   {
      case GFX_CTX_VULKAN_API:
#if defined(HAVE_VULKAN) && defined(HAVE_THREADS)
         if (wl->vk.context.queue_lock)
            slock_free(wl->vk.context.queue_lock);
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   free(wl);
}