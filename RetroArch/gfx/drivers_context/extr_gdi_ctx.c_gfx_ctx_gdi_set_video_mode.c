#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  gfx_ctx_gdi_destroy (void*) ; 
 int /*<<< orphan*/  win32_set_video_mode (int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static bool gfx_ctx_gdi_set_video_mode(void *data,
      video_frame_info_t *video_info,
      unsigned width, unsigned height,
      bool fullscreen)
{
   if (!win32_set_video_mode(NULL, width, height, fullscreen))
   {
      RARCH_ERR("[GDI]: win32_set_video_mode failed.\n");
      gfx_ctx_gdi_destroy(data);
      return false;
   }

   return true;
}