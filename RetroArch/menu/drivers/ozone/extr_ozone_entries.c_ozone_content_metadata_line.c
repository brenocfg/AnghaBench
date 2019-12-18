#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ video_frame_info_t ;
struct TYPE_10__ {int /*<<< orphan*/  footer; } ;
struct TYPE_12__ {TYPE_1__* theme; TYPE_2__ fonts; } ;
typedef  TYPE_4__ ozone_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  text_rgba; } ;

/* Variables and functions */
 unsigned int FONT_SIZE_FOOTER ; 
 int /*<<< orphan*/  TEXT_ALIGN_LEFT ; 
 int font_driver_get_line_height (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ozone_draw_text (TYPE_3__*,TYPE_4__*,char const*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ozone_content_metadata_line(video_frame_info_t *video_info, ozone_handle_t *ozone,
   unsigned *y, unsigned column_x, const char *text, unsigned lines_count)
{
   int line_height = font_driver_get_line_height(ozone->fonts.footer, 1);

   ozone_draw_text(video_info, ozone,
      text,
      column_x,
      *y + FONT_SIZE_FOOTER,
      TEXT_ALIGN_LEFT,
      video_info->width, video_info->height,
      ozone->fonts.footer,
      ozone->theme->text_rgba,
      true
   );

   if (lines_count > 0)
      *y += (unsigned)(line_height * (lines_count - 1)) + (unsigned)((float)line_height * 1.5f);
}