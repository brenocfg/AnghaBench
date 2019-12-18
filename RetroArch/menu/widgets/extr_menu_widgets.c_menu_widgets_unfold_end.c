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
struct TYPE_2__ {int unfolding; } ;
typedef  TYPE_1__ menu_widget_msg_t ;

/* Variables and functions */
 int widgets_moving ; 

__attribute__((used)) static void menu_widgets_unfold_end(void *userdata)
{
   menu_widget_msg_t *unfold = (menu_widget_msg_t*) userdata;

   unfold->unfolding = false;
   widgets_moving    = false;
}