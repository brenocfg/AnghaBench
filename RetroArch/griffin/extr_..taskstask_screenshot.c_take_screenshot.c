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
 int /*<<< orphan*/  runloop_get_status (int*,int*,int*,int*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int take_screenshot_choice (char const*,char const*,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_cached_frame () ; 
 int /*<<< orphan*/  video_driver_get_pixel_format () ; 
 scalar_t__ video_driver_prefer_viewport_read () ; 
 int /*<<< orphan*/  video_driver_supports_read_frame_raw () ; 
 scalar_t__ video_driver_supports_viewport_read () ; 

bool take_screenshot(
      const char *screenshot_dir,
      const char *name_base,
      bool silence, bool has_valid_framebuffer,
      bool fullpath, bool use_thread)
{
   bool is_paused              = false;
   bool is_idle                = false;
   bool is_slowmotion          = false;
   bool is_perfcnt_enable      = false;
   bool ret                    = false;

   runloop_get_status(&is_paused, &is_idle, &is_slowmotion, &is_perfcnt_enable);

   /* No way to infer screenshot directory. */
   if (     string_is_empty(screenshot_dir)
         && string_is_empty(name_base))
      return false;

   ret       = take_screenshot_choice(
         screenshot_dir,
         name_base, silence, is_paused, is_idle,
         has_valid_framebuffer, fullpath, use_thread,
         video_driver_supports_viewport_read() &&
         video_driver_prefer_viewport_read(),
         video_driver_supports_read_frame_raw(),
         video_driver_get_pixel_format()
         );

   if (is_paused && !is_idle)
         video_driver_cached_frame();

   return ret;
}