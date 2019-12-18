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
struct TYPE_2__ {void* (* get_resolution_list ) (int /*<<< orphan*/ ,unsigned int*) ;} ;

/* Variables and functions */
 TYPE_1__* current_display_server ; 
 int /*<<< orphan*/  current_display_server_data ; 
 void* stub1 (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ video_display_server_has_resolution_list () ; 

void *video_display_server_get_resolution_list(unsigned *size)
{
   if (video_display_server_has_resolution_list())
      return current_display_server->get_resolution_list(current_display_server_data, size);
   return NULL;
}