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
struct TYPE_3__ {int max_swapchain_images; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct TYPE_4__ {int vsync_callback_set; int /*<<< orphan*/  dispman_display; int /*<<< orphan*/  vsync_condition_mutex; int /*<<< orphan*/  vsync_condition; int /*<<< orphan*/  egl; } ;
typedef  TYPE_2__ vc_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dispmanx_vsync_callback ; 
 int /*<<< orphan*/  egl_swap_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_vsync_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void gfx_ctx_vc_swap_buffers(void *data, void *data2)
{
#ifdef HAVE_EGL
   vc_ctx_data_t              *vc = (vc_ctx_data_t*)data;
   video_frame_info_t *video_info = (video_frame_info_t*)data2;

   if (!vc)
      return;

   egl_swap_buffers(&vc->egl);

   /* Wait for vsync immediately if we don't
    * want egl_swap_buffers to triple-buffer */
   if (video_info->max_swapchain_images <= 2)
   {
      /* We DON'T wait to wait without callback function ready! */
      if (!vc->vsync_callback_set)
      {
         vc_dispmanx_vsync_callback(vc->dispman_display,
               dispmanx_vsync_callback, (void*)vc);
         vc->vsync_callback_set = true;
      }
      slock_lock(vc->vsync_condition_mutex);
      scond_wait(vc->vsync_condition, vc->vsync_condition_mutex);
      slock_unlock(vc->vsync_condition_mutex);
   }
   /* Stop generating vsync callbacks from now on */
   else if (vc->vsync_callback_set)
      vc_dispmanx_vsync_callback(vc->dispman_display, NULL, NULL);
#endif
}