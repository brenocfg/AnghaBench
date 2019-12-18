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
struct TYPE_2__ {int /*<<< orphan*/  egl; } ;
typedef  TYPE_1__ qnx_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  egl_get_video_size (int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void gfx_ctx_qnx_check_window(void *data, bool *quit,
      bool *resize, unsigned *width, unsigned *height,
      bool is_shutdown)
{
   unsigned new_width, new_height;
   qnx_ctx_data_t *qnx = (qnx_ctx_data_t*)data;

   *quit = false;

#ifdef HAVE_EGL
   egl_get_video_size(&qnx->egl, &new_width, &new_height);
#endif

   if (new_width != *width || new_height != *height)
   {
      *width  = new_width;
      *height = new_height;
      *resize = true;
   }

   /* Check if we are exiting. */
   if (is_shutdown)
      *quit = true;
}