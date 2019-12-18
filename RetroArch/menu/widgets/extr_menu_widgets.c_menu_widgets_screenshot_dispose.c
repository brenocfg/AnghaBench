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
 int screenshot_loaded ; 
 int /*<<< orphan*/  screenshot_texture ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_widgets_screenshot_dispose(void *userdata)
{
   screenshot_loaded = false;
   video_driver_texture_unload(&screenshot_texture);
}