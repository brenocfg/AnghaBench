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
struct TYPE_2__ {int (* set_resolution ) (int /*<<< orphan*/ ,unsigned int,unsigned int,int,float,int,int,int) ;} ;

/* Variables and functions */
 TYPE_1__* current_display_server ; 
 int /*<<< orphan*/  current_display_server_data ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int,int,float,int,int,int) ; 

bool video_display_server_set_resolution(unsigned width, unsigned height,
      int int_hz, float hz, int center, int monitor_index, int xoffset)
{
   if (current_display_server && current_display_server->set_resolution)
      return current_display_server->set_resolution(current_display_server_data, width, height, int_hz, hz, center, monitor_index, xoffset);
   return false;
}