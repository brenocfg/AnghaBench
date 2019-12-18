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
struct netplay_connection {scalar_t__ mode; scalar_t__ active; } ;
struct TYPE_5__ {size_t connections_size; struct netplay_connection* connections; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 scalar_t__ NETPLAY_CONNECTION_CONNECTED ; 
 int /*<<< orphan*/  netplay_hangup (TYPE_1__*,struct netplay_connection*) ; 
 int /*<<< orphan*/  netplay_send_raw_cmd (TYPE_1__*,struct netplay_connection*,int /*<<< orphan*/ ,void const*,size_t) ; 

void netplay_send_raw_cmd_all(netplay_t *netplay,
   struct netplay_connection *except, uint32_t cmd, const void *data,
   size_t size)
{
   size_t i;
   for (i = 0; i < netplay->connections_size; i++)
   {
      struct netplay_connection *connection = &netplay->connections[i];
      if (connection == except)
         continue;
      if (connection->active && connection->mode >= NETPLAY_CONNECTION_CONNECTED)
      {
         if (!netplay_send_raw_cmd(netplay, connection, cmd, data, size))
            netplay_hangup(netplay, connection);
      }
   }
}