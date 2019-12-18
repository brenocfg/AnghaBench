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
 int /*<<< orphan*/  cheevo_badge ; 
 int /*<<< orphan*/  cheevo_title ; 
 int /*<<< orphan*/  menu_widgets_achievement_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_widgets_get_badge_texture (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  menu_widgets_start_achievement_notification () ; 
 int /*<<< orphan*/  strdup (char const*) ; 

void menu_widgets_push_achievement(const char *title, const char *badge)
{
   menu_widgets_achievement_free(NULL);

   /* TODO: Make a queue of notifications to display */

   cheevo_title = strdup(title);
   menu_widgets_get_badge_texture(&cheevo_badge, badge);

   menu_widgets_start_achievement_notification();
}