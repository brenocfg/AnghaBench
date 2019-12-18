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
 float DEFAULT_MENU_THUMBNAIL_STREAM_DELAY ; 
 float menu_thumbnail_stream_delay ; 

void menu_thumbnail_set_stream_delay(float delay)
{
   menu_thumbnail_stream_delay = (delay >= 0.0f) ?
         delay : DEFAULT_MENU_THUMBNAIL_STREAM_DELAY;
}