#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t connections_size; int /*<<< orphan*/ * connections; } ;
typedef  TYPE_1__ netplay_t ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ discord_userdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_DISCORD_UPDATE ; 
 int /*<<< orphan*/  DISCORD_PRESENCE_NETPLAY_NETPLAY_STOPPED ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  deinit_netplay () ; 
 scalar_t__ discord_is_inited ; 
 int /*<<< orphan*/  netplay_hangup (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool netplay_disconnect(netplay_t *netplay)
{
   size_t i;

   if (!netplay)
      return true;
   for (i = 0; i < netplay->connections_size; i++)
      netplay_hangup(netplay, &netplay->connections[i]);

   deinit_netplay();

#ifdef HAVE_DISCORD
   if (discord_is_inited)
   {
      discord_userdata_t userdata;
      userdata.status = DISCORD_PRESENCE_NETPLAY_NETPLAY_STOPPED;
      command_event(CMD_EVENT_DISCORD_UPDATE, &userdata);
   }
#endif
   return true;
}