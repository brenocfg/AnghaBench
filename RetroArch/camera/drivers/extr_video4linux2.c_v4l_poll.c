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
struct TYPE_2__ {int width; int /*<<< orphan*/  height; int /*<<< orphan*/  buffer_output; int /*<<< orphan*/  ready; } ;
typedef  TYPE_1__ video4linux_t ;
typedef  int /*<<< orphan*/  (* retro_camera_frame_raw_framebuffer_t ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;
typedef  int /*<<< orphan*/  retro_camera_frame_opengl_texture_t ;

/* Variables and functions */
 scalar_t__ preprocess_image (void*) ; 

__attribute__((used)) static bool v4l_poll(void *data,
      retro_camera_frame_raw_framebuffer_t frame_raw_cb,
      retro_camera_frame_opengl_texture_t frame_gl_cb)
{
   video4linux_t *v4l = (video4linux_t*)data;
   if (!v4l->ready)
      return false;

   (void)frame_gl_cb;

   if (preprocess_image(data))
   {
      if (frame_raw_cb != NULL)
         frame_raw_cb(v4l->buffer_output, v4l->width,
               v4l->height, v4l->width * 4);
      return true;
   }

   return false;
}