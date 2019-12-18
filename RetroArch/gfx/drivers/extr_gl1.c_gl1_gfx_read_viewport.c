#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {unsigned int width; unsigned int height; } ;
struct TYPE_5__ {int /*<<< orphan*/ * readback_buffer_screenshot; TYPE_1__ vp; } ;
typedef  TYPE_2__ gl1_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl1_context_bind_hw_render (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * malloc (unsigned int) ; 
 int /*<<< orphan*/  video_driver_cached_frame () ; 
 int /*<<< orphan*/  video_frame_convert_rgba_to_bgr (void const*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static bool gl1_gfx_read_viewport(void *data, uint8_t *buffer, bool is_idle)
{
   unsigned num_pixels = 0;
   gl1_t *gl1 = (gl1_t*)data;

   if (!gl1)
      return false;

   gl1_context_bind_hw_render(gl1, false);

   num_pixels = gl1->vp.width * gl1->vp.height;

   gl1->readback_buffer_screenshot = malloc(num_pixels * sizeof(uint32_t));

   if (!gl1->readback_buffer_screenshot)
      goto error;

   if (!is_idle)
      video_driver_cached_frame();

   video_frame_convert_rgba_to_bgr(
         (const void*)gl1->readback_buffer_screenshot,
         buffer,
         num_pixels);

   free(gl1->readback_buffer_screenshot);
   gl1->readback_buffer_screenshot = NULL;

   gl1_context_bind_hw_render(gl1, true);
   return true;

error:
   gl1_context_bind_hw_render(gl1, true);

   return false;
}