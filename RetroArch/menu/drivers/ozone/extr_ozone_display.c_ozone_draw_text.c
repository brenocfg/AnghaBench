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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ozone_handle_t ;
typedef  int /*<<< orphan*/  font_data_t ;
typedef  enum text_alignment { ____Placeholder_text_alignment } text_alignment ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_draw_text (int /*<<< orphan*/ *,char const*,float,float,unsigned int,unsigned int,int /*<<< orphan*/ ,int,float,int,double,int) ; 

void ozone_draw_text(
      video_frame_info_t *video_info,
      ozone_handle_t *ozone,
      const char *str, float x,
      float y,
      enum text_alignment text_align,
      unsigned width, unsigned height, font_data_t* font,
      uint32_t color,
      bool draw_outside)
{
   menu_display_draw_text(font, str, x, y,
         width, height, color, text_align, 1.0f,
         false,
         1.0, draw_outside);
}