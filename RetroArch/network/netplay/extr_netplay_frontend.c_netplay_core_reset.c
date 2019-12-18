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
typedef  int /*<<< orphan*/  uint32_t ;
struct netplay_connection {scalar_t__ mode; int /*<<< orphan*/  fd; int /*<<< orphan*/  send_packet_buffer; int /*<<< orphan*/  active; } ;
struct TYPE_5__ {int self_frame_count; size_t connections_size; struct netplay_connection* connections; } ;
typedef  TYPE_1__ netplay_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int NETPLAY_CMD_RESET ; 
 scalar_t__ NETPLAY_CONNECTION_CONNECTED ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  netplay_force_future (TYPE_1__*) ; 
 int /*<<< orphan*/  netplay_hangup (TYPE_1__*,struct netplay_connection*) ; 
 int /*<<< orphan*/  netplay_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void netplay_core_reset(netplay_t *netplay)
{
   uint32_t cmd[3];
   size_t i;

   /* Ignore past input */
   netplay_force_future(netplay);

   /* Request that our peers reset */
   cmd[0] = htonl(NETPLAY_CMD_RESET);
   cmd[1] = htonl(sizeof(uint32_t));
   cmd[2] = htonl(netplay->self_frame_count);

   for (i = 0; i < netplay->connections_size; i++)
   {
      struct netplay_connection *connection = &netplay->connections[i];
      if (!connection->active ||
            connection->mode < NETPLAY_CONNECTION_CONNECTED) continue;

      if (!netplay_send(&connection->send_packet_buffer, connection->fd, cmd,
               sizeof(cmd)))
         netplay_hangup(netplay, connection);
   }
}