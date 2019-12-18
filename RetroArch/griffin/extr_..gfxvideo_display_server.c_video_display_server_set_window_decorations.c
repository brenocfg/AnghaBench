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
struct TYPE_2__ {int (* set_window_decorations ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_1__* current_display_server ; 
 int /*<<< orphan*/  current_display_server_data ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

bool video_display_server_set_window_decorations(bool on)
{
   if (current_display_server && current_display_server->set_window_decorations)
      return current_display_server->set_window_decorations(current_display_server_data, on);
   return false;
}