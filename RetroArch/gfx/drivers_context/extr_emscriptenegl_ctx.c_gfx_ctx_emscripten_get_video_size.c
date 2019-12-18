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
struct TYPE_2__ {unsigned int fb_width; unsigned int fb_height; } ;
typedef  TYPE_1__ emscripten_ctx_data_t ;

/* Variables and functions */

__attribute__((used)) static void gfx_ctx_emscripten_get_video_size(void *data,
      unsigned *width, unsigned *height)
{
   emscripten_ctx_data_t *emscripten = (emscripten_ctx_data_t*)data;

   if (!emscripten)
      return;

   *width  = emscripten->fb_width;
   *height = emscripten->fb_height;
}