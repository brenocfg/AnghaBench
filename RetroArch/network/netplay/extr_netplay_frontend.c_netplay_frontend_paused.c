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
typedef  int uint32_t ;
struct netplay_connection {scalar_t__ mode; int /*<<< orphan*/  fd; int /*<<< orphan*/  send_packet_buffer; scalar_t__ active; scalar_t__ paused; } ;
struct TYPE_4__ {int local_paused; size_t connections_size; int /*<<< orphan*/ * nick; struct netplay_connection* connections; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_CMD_PAUSE ; 
 int /*<<< orphan*/  NETPLAY_CMD_RESUME ; 
 scalar_t__ NETPLAY_CONNECTION_CONNECTED ; 
 int /*<<< orphan*/  NETPLAY_NICK_LEN ; 
 int /*<<< orphan*/  netplay_send_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netplay_send_raw_cmd (TYPE_1__*,struct netplay_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netplay_frontend_paused(netplay_t *netplay, bool paused)
{
   size_t i;
   uint32_t paused_ct;

   /* Nothing to do if we already knew this */
   if (netplay->local_paused == paused)
      return;

   netplay->local_paused = paused;

   /* Communicating this is a bit odd: If exactly one other connection is
    * paused, then we must tell them that we're unpaused, as from their
    * perspective we are. If more than one other connection is paused, then our
    * status as proxy means we are NOT unpaused to either of them. */
   paused_ct = 0;
   for (i = 0; i < netplay->connections_size; i++)
   {
      struct netplay_connection *connection = &netplay->connections[i];
      if (connection->active && connection->paused)
         paused_ct++;
   }
   if (paused_ct > 1)
      return;

   /* Send our unpaused status. Must send manually because we must immediately
    * flush the buffer: If we're paused, we won't be polled. */
   for (i = 0; i < netplay->connections_size; i++)
   {
      struct netplay_connection *connection = &netplay->connections[i];
      if (connection->active && connection->mode >= NETPLAY_CONNECTION_CONNECTED)
      {
         if (paused)
            netplay_send_raw_cmd(netplay, connection, NETPLAY_CMD_PAUSE,
               netplay->nick, NETPLAY_NICK_LEN);
         else
            netplay_send_raw_cmd(netplay, connection, NETPLAY_CMD_RESUME,
               NULL, 0);

         /* We're not going to be polled, so we need to flush this command now */
         netplay_send_flush(&connection->send_packet_buffer, connection->fd, true);
      }
   }
}