#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ video_frame_info_t ;
struct TYPE_11__ {int /*<<< orphan*/  cursor_border; int /*<<< orphan*/  cursor_alpha; } ;
struct TYPE_13__ {int /*<<< orphan*/ * textures; TYPE_2__ theme_dynamic; TYPE_1__* theme; } ;
typedef  TYPE_4__ ozone_handle_t ;
struct TYPE_10__ {int /*<<< orphan*/ * textures; } ;

/* Variables and functions */
 size_t OZONE_TEXTURE_CURSOR_BORDER ; 
 size_t OZONE_THEME_TEXTURE_CURSOR_NO_BORDER ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_display_blend_end (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_display_draw_texture_slice (TYPE_3__*,int,int,int,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_set_alpha (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void ozone_draw_cursor_slice(ozone_handle_t *ozone,
      video_frame_info_t *video_info,
      int x_offset,
      unsigned width, unsigned height,
      size_t y, float alpha)
{
   menu_display_set_alpha(ozone->theme_dynamic.cursor_alpha, alpha);
   menu_display_set_alpha(ozone->theme_dynamic.cursor_border, alpha);

   menu_display_blend_begin(video_info);

   /* Cursor without border */
   menu_display_draw_texture_slice(
      video_info,
      x_offset - 14,
      (int)(y + 8),
      80, 80,
      width + 3 + 28 - 4,
      height + 20,
      video_info->width, video_info->height,
      ozone->theme_dynamic.cursor_alpha,
      20, 1.0,
      ozone->theme->textures[OZONE_THEME_TEXTURE_CURSOR_NO_BORDER]
   );

   /* Tainted border */
   menu_display_draw_texture_slice(
      video_info,
      x_offset - 14,
      (int)(y + 8),
      80, 80,
      width + 3 + 28 - 4,
      height + 20,
      video_info->width, video_info->height,
      ozone->theme_dynamic.cursor_border,
      20, 1.0,
      ozone->textures[OZONE_TEXTURE_CURSOR_BORDER]
   );

   menu_display_blend_end(video_info);
}