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
struct TYPE_2__ {int view_changed; } ;

/* Variables and functions */
 TYPE_1__* video_layout_state ; 

bool video_layout_view_on_change(void)
{
   if (video_layout_state->view_changed)
   {
      video_layout_state->view_changed = false;
      return true;
   }
   return false;
}