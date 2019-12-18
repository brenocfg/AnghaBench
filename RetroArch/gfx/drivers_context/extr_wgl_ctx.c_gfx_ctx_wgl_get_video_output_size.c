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

/* Variables and functions */
 int /*<<< orphan*/  win32_get_video_output_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static void gfx_ctx_wgl_get_video_output_size(void *data,
      unsigned *width, unsigned *height)
{
   win32_get_video_output_size(width, height);
}