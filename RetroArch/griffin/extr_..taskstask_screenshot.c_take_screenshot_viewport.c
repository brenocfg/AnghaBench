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
typedef  int /*<<< orphan*/  uint8_t ;
struct video_viewport {int width; int height; scalar_t__ full_height; scalar_t__ full_width; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  screenshot_dump (char const*,char const*,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *,int,int,int,int,int,unsigned int) ; 
 int /*<<< orphan*/  video_driver_get_viewport_info (struct video_viewport*) ; 
 int /*<<< orphan*/  video_driver_read_viewport (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool take_screenshot_viewport(
      const char *screenshot_dir,
      const char *name_base,
      bool savestate,
      bool is_idle,
      bool is_paused,
      bool fullpath,
      bool use_thread,
      unsigned pixel_format_type)
{
   struct video_viewport vp;
   uint8_t *buffer                       = NULL;

   vp.x                                  = 0;
   vp.y                                  = 0;
   vp.width                              = 0;
   vp.height                             = 0;
   vp.full_width                         = 0;
   vp.full_height                        = 0;

   video_driver_get_viewport_info(&vp);

   if (!vp.width || !vp.height)
      return false;

   buffer = (uint8_t*)malloc(vp.width * vp.height * 3);

   if (!buffer)
      return false;

   if (!video_driver_read_viewport(buffer, is_idle))
   {
      free(buffer);
      return false;
   }

   /* Data read from viewport is in bottom-up order, suitable for BMP. */
   if (!screenshot_dump(screenshot_dir,
            name_base,
            buffer, vp.width, vp.height,
            vp.width * 3, true, buffer,
            savestate, is_idle, is_paused, fullpath, use_thread,
            pixel_format_type))
   {
      free(buffer);
      return false;
   }

   return true;
}