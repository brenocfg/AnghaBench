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
typedef  int uint32_t ;
struct netplay_connection {int /*<<< orphan*/  fd; int /*<<< orphan*/  send_packet_buffer; } ;
struct delta_frame {scalar_t__* have_real; } ;
typedef  int /*<<< orphan*/  payload ;
struct TYPE_5__ {size_t self_ptr; int connected_players; scalar_t__ self_mode; int self_client_num; int /*<<< orphan*/  self_frame_count; struct netplay_connection* connections; scalar_t__ is_server; struct delta_frame* buffer; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  NETPLAY_CMD_NOINPUT ; 
 scalar_t__ NETPLAY_CONNECTION_PLAYING ; 
 scalar_t__ NETPLAY_CONNECTION_SLAVE ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netplay_send_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netplay_send_raw_cmd (TYPE_1__*,struct netplay_connection*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  send_input_frame (TYPE_1__*,struct delta_frame*,struct netplay_connection*,int /*<<< orphan*/ *,int,int) ; 

bool netplay_send_cur_input(netplay_t *netplay,
   struct netplay_connection *connection)
{
   uint32_t from_client, to_client;
   struct delta_frame *dframe = &netplay->buffer[netplay->self_ptr];

   if (netplay->is_server)
   {
      to_client = (uint32_t)(connection - netplay->connections + 1);

      /* Send the other players' input data (FIXME: This involves an
       * unacceptable amount of recalculating) */
      for (from_client = 1; from_client < MAX_CLIENTS; from_client++)
      {
         if (from_client == to_client)
            continue;

         if ((netplay->connected_players & (1<<from_client)))
         {
            if (dframe->have_real[from_client])
            {
               if (!send_input_frame(netplay, dframe, connection, NULL, from_client, false))
                  return false;
            }
         }
      }

      /* If we're not playing, send a NOINPUT */
      if (netplay->self_mode != NETPLAY_CONNECTION_PLAYING)
      {
         uint32_t payload = htonl(netplay->self_frame_count);
         if (!netplay_send_raw_cmd(netplay, connection, NETPLAY_CMD_NOINPUT,
               &payload, sizeof(payload)))
            return false;
      }

   }

   /* Send our own data */
   if (netplay->self_mode == NETPLAY_CONNECTION_PLAYING
         || netplay->self_mode == NETPLAY_CONNECTION_SLAVE)
   {
      if (!send_input_frame(netplay, dframe, connection, NULL,
            netplay->self_client_num,
            netplay->self_mode == NETPLAY_CONNECTION_SLAVE))
         return false;
   }

   if (!netplay_send_flush(&connection->send_packet_buffer, connection->fd,
         false))
      return false;

   return true;
}