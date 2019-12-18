#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct netplay_connection {int paused; scalar_t__ active; } ;
struct TYPE_4__ {int remote_paused; size_t connections_size; int /*<<< orphan*/  local_paused; struct netplay_connection* connections; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_CMD_RESUME ; 
 int /*<<< orphan*/  netplay_send_raw_cmd_all (TYPE_1__*,struct netplay_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remote_unpaused(netplay_t *netplay, struct netplay_connection *connection)
{
    size_t i;
    connection->paused = false;
    netplay->remote_paused = false;
    for (i = 0; i < netplay->connections_size; i++)
    {
       struct netplay_connection *sc = &netplay->connections[i];
       if (sc->active && sc->paused)
       {
          netplay->remote_paused = true;
          break;
       }
    }
    if (!netplay->remote_paused && !netplay->local_paused)
       netplay_send_raw_cmd_all(netplay, connection, NETPLAY_CMD_RESUME, NULL, 0);
}