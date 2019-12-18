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
 int MENU_WIDGETS_ICON_LAST ; 
 int /*<<< orphan*/ * font_bold ; 
 int /*<<< orphan*/ * font_regular ; 
 int /*<<< orphan*/  menu_display_font_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * menu_widgets_icons_textures ; 
 int /*<<< orphan*/  msg_queue_icon ; 
 int /*<<< orphan*/  msg_queue_icon_outline ; 
 int /*<<< orphan*/  msg_queue_icon_rect ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

void menu_widgets_context_destroy(void)
{
   int i;

   /* TODO: Dismiss onscreen notifications that have been freed */

   /* Textures */
   for (i = 0; i < MENU_WIDGETS_ICON_LAST; i++)
   {
      video_driver_texture_unload(&menu_widgets_icons_textures[i]);
   }

   video_driver_texture_unload(&msg_queue_icon);
   video_driver_texture_unload(&msg_queue_icon_outline);
   video_driver_texture_unload(&msg_queue_icon_rect);

   /* Fonts */
   menu_display_font_free(font_regular);
   menu_display_font_free(font_bold);

   font_regular = NULL;
   font_bold = NULL;
}