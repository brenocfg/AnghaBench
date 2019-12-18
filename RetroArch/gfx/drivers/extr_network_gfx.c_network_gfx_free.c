#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fd; } ;
typedef  TYPE_1__ network_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  font_driver_free_osd () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* network_menu_frame ; 
 TYPE_1__* network_video_temp_buf ; 
 int /*<<< orphan*/  socket_close (scalar_t__) ; 

__attribute__((used)) static void network_gfx_free(void *data)
{
   network_video_t *network = (network_video_t*)data;

   if (network_menu_frame)
   {
      free(network_menu_frame);
      network_menu_frame = NULL;
   }

   if (network_video_temp_buf)
   {
      free(network_video_temp_buf);
      network_video_temp_buf = NULL;
   }

   font_driver_free_osd();

   if (network->fd >= 0)
      socket_close(network->fd);

   if (network)
      free(network);
}