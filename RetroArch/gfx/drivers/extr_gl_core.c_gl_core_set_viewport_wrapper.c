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
typedef  int /*<<< orphan*/  gl_core_t ;

/* Variables and functions */
 int /*<<< orphan*/  gl_core_set_viewport (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  video_driver_build_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl_core_set_viewport_wrapper(void *data,
      unsigned viewport_width,
      unsigned viewport_height, bool force_full, bool allow_rotate)
{
   video_frame_info_t video_info;
   gl_core_t *gl = (gl_core_t*)data;

   video_driver_build_info(&video_info);

   gl_core_set_viewport(gl, &video_info,
         viewport_width, viewport_height, force_full, allow_rotate);
}