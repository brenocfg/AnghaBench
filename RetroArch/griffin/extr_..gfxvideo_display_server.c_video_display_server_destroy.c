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
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (scalar_t__) ;} ;

/* Variables and functions */
 TYPE_1__* current_display_server ; 
 scalar_t__ current_display_server_data ; 
 scalar_t__ current_screen_orientation ; 
 scalar_t__ initial_screen_orientation ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  video_display_server_set_screen_orientation (scalar_t__) ; 

void video_display_server_destroy(void)
{
   if (initial_screen_orientation != current_screen_orientation)
      video_display_server_set_screen_orientation(initial_screen_orientation);

   if (current_display_server && current_display_server->destroy)
      if (current_display_server_data)
         current_display_server->destroy(current_display_server_data);
}