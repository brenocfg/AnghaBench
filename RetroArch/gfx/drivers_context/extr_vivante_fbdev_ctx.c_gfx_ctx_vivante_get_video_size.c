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
typedef  TYPE_1__ vivante_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  egl_get_video_size (int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void gfx_ctx_vivante_get_video_size(void *data,
      unsigned *width, unsigned *height)
{
   vivante_ctx_data_t *viv = (vivante_ctx_data_t*)data;

#ifdef HAVE_EGL
   egl_get_video_size(&viv->egl, width, height);
#endif
}