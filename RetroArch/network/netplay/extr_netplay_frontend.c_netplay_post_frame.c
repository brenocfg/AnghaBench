#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct netplay_connection {scalar_t__ active; int /*<<< orphan*/  fd; int /*<<< orphan*/  send_packet_buffer; } ;
struct TYPE_8__ {size_t connections_size; struct netplay_connection* connections; int /*<<< orphan*/  is_server; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  netplay_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  netplay_hangup (TYPE_1__*,struct netplay_connection*) ; 
 int /*<<< orphan*/  netplay_send_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netplay_sync_post_frame (TYPE_1__*,int) ; 
 int /*<<< orphan*/  netplay_update_unread_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  retro_assert (TYPE_1__*) ; 

void netplay_post_frame(netplay_t *netplay)
{
   size_t i;
   retro_assert(netplay);
   netplay_update_unread_ptr(netplay);
   netplay_sync_post_frame(netplay, false);

   for (i = 0; i < netplay->connections_size; i++)
   {
      struct netplay_connection *connection = &netplay->connections[i];
      if (connection->active &&
          !netplay_send_flush(&connection->send_packet_buffer, connection->fd,
            false))
         netplay_hangup(netplay, connection);
   }

   /* If we're disconnected, deinitialize */
   if (!netplay->is_server && !netplay->connections[0].active)
      netplay_disconnect(netplay);
}