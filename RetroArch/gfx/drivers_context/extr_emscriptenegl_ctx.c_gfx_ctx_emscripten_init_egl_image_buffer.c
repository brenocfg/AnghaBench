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
typedef  int /*<<< orphan*/  video_info_t ;

/* Variables and functions */

__attribute__((used)) static bool gfx_ctx_emscripten_init_egl_image_buffer(void *data,
      const video_info_t *video)
{
   (void)data;

   return false;
}