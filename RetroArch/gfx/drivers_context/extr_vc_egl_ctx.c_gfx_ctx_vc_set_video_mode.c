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
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  interval; } ;
struct TYPE_3__ {TYPE_2__ egl; } ;
typedef  TYPE_1__ vc_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  frontend_driver_install_signal_handler () ; 
 int g_egl_inited ; 
 int /*<<< orphan*/  gfx_ctx_vc_set_swap_interval (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gfx_ctx_vc_set_video_mode(void *data,
      video_frame_info_t *video_info,
      unsigned width, unsigned height,
      bool fullscreen)
{
#ifdef HAVE_EGL
   vc_ctx_data_t *vc = (vc_ctx_data_t*)data;
   if (!vc || g_egl_inited)
      return false;

   frontend_driver_install_signal_handler();

   gfx_ctx_vc_set_swap_interval(&vc->egl, vc->egl.interval);

   g_egl_inited = true;
#endif

   return true;
}