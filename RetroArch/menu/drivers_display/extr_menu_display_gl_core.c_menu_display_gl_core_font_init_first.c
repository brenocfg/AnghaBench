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
typedef  int /*<<< orphan*/  font_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  FONT_DRIVER_RENDER_OPENGL_CORE_API ; 
 int /*<<< orphan*/ * font_driver_init_first (void*,char const*,float,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool menu_display_gl_core_font_init_first(
      void **font_handle, void *video_data, const char *font_path,
      float menu_font_size, bool is_threaded)
{
   font_data_t **handle = (font_data_t**)font_handle;
   *handle = font_driver_init_first(video_data,
         font_path, menu_font_size, true,
         is_threaded,
         FONT_DRIVER_RENDER_OPENGL_CORE_API);

   if (*handle)
      return true;

   return false;
}