#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum rotation { ____Placeholder_rotation } rotation ;
struct TYPE_2__ {int (* get_screen_orientation ) () ;} ;

/* Variables and functions */
 int ORIENTATION_NORMAL ; 
 TYPE_1__* current_display_server ; 
 int stub1 () ; 

enum rotation video_display_server_get_screen_orientation(void)
{
   if (current_display_server && current_display_server->get_screen_orientation)
      return current_display_server->get_screen_orientation();
   return ORIENTATION_NORMAL;
}