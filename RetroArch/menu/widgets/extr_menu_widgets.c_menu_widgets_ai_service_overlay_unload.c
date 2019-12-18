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
 int ai_service_overlay_state ; 
 int /*<<< orphan*/  ai_service_overlay_texture ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

void menu_widgets_ai_service_overlay_unload()
{
   if (ai_service_overlay_state == 1)
   {
      video_driver_texture_unload(&ai_service_overlay_texture);
      ai_service_overlay_state = 0;
   }
}