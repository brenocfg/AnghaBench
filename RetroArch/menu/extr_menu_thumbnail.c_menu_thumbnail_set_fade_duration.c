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
 float DEFAULT_MENU_THUMBNAIL_FADE_DURATION ; 
 float menu_thumbnail_fade_duration ; 

void menu_thumbnail_set_fade_duration(float duration)
{
   menu_thumbnail_fade_duration = (duration >= 0.0f) ?
         duration : DEFAULT_MENU_THUMBNAIL_FADE_DURATION;
}