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

/* Variables and functions */
 int /*<<< orphan*/  screenshot_dump (char const*,char const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,int,int,void*,int,int,int,int,int,unsigned int) ; 
 int /*<<< orphan*/  video_driver_cached_frame_get (void const**,unsigned int*,unsigned int*,size_t*) ; 

__attribute__((used)) static bool take_screenshot_raw(const char *screenshot_dir,
      const char *name_base, void *userbuf,
      bool savestate, bool is_idle, bool is_paused, bool fullpath, bool use_thread,
      unsigned pixel_format_type)
{
   size_t pitch;
   unsigned width, height;
   const void *data                      = NULL;

   video_driver_cached_frame_get(&data, &width, &height, &pitch);

   /* Negative pitch is needed as screenshot takes bottom-up,
    * but we use top-down.
    */
   if (!screenshot_dump(screenshot_dir,
            name_base,
            (const uint8_t*)data + (height - 1) * pitch,
            width,
            height,
            (int)(-pitch),
            false,
            userbuf,
            savestate,
            is_idle,
            is_paused,
            fullpath,
            use_thread,
            pixel_format_type))
      return false;

   return true;
}