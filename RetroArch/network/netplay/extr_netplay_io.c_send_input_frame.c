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
typedef  size_t uint32_t ;
struct netplay_connection {scalar_t__ mode; int /*<<< orphan*/  fd; int /*<<< orphan*/  send_packet_buffer; scalar_t__ active; } ;
struct delta_frame {size_t frame; TYPE_2__** real_input; } ;
struct TYPE_6__ {size_t* client_devices; size_t connections_size; struct netplay_connection* connections; } ;
typedef  TYPE_1__ netplay_t ;
typedef  TYPE_2__* netplay_input_state_t ;
struct TYPE_7__ {size_t client_num; size_t size; size_t* data; struct TYPE_7__* next; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int BUFSZ ; 
 size_t MAX_CLIENTS ; 
 size_t MAX_INPUT_DEVICES ; 
 size_t NETPLAY_CMD_INPUT ; 
 scalar_t__ NETPLAY_CONNECTION_CONNECTED ; 
 scalar_t__ NETPLAY_CONNECTION_PLAYING ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int) ; 
 size_t htonl (size_t) ; 
 int /*<<< orphan*/  netplay_hangup (TYPE_1__*,struct netplay_connection*) ; 
 int /*<<< orphan*/  netplay_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,size_t) ; 
 int /*<<< orphan*/  print_state (TYPE_1__*) ; 

__attribute__((used)) static bool send_input_frame(netplay_t *netplay, struct delta_frame *dframe,
      struct netplay_connection *only, struct netplay_connection *except,
      uint32_t client_num, bool slave)
{
#define BUFSZ 16 /* FIXME: Arbitrary restriction */
   uint32_t buffer[BUFSZ], devices, device;
   size_t bufused, i;

   /* Set up the basic buffer */
   bufused = 4;
   buffer[0] = htonl(NETPLAY_CMD_INPUT);
   buffer[2] = htonl(dframe->frame);
   buffer[3] = htonl(client_num);

   /* Add the device data */
   devices = netplay->client_devices[client_num];
   for (device = 0; device < MAX_INPUT_DEVICES; device++)
   {
      netplay_input_state_t istate;
      if (!(devices & (1<<device)))
         continue;
      istate = dframe->real_input[device];
      while (istate && (!istate->used || istate->client_num != (slave?MAX_CLIENTS:client_num)))
         istate = istate->next;
      if (!istate)
         continue;
      if (bufused + istate->size >= BUFSZ)
         continue; /* FIXME: More severe? */
      for (i = 0; i < istate->size; i++)
         buffer[bufused+i] = htonl(istate->data[i]);
      bufused += istate->size;
   }
   buffer[1] = htonl((bufused-2) * sizeof(uint32_t));

#ifdef DEBUG_NETPLAY_STEPS
   RARCH_LOG("[netplay] Sending input for client %u\n", (unsigned) client_num);
   print_state(netplay);
#endif

   if (only)
   {
      if (!netplay_send(&only->send_packet_buffer, only->fd, buffer, bufused*sizeof(uint32_t)))
      {
         netplay_hangup(netplay, only);
         return false;
      }
   }
   else
   {
      for (i = 0; i < netplay->connections_size; i++)
      {
         struct netplay_connection *connection = &netplay->connections[i];
         if (connection == except)
            continue;
         if (connection->active &&
             connection->mode >= NETPLAY_CONNECTION_CONNECTED &&
             (connection->mode != NETPLAY_CONNECTION_PLAYING ||
              i+1 != client_num))
         {
            if (!netplay_send(&connection->send_packet_buffer, connection->fd,
                  buffer, bufused*sizeof(uint32_t)))
               netplay_hangup(netplay, connection);
         }
      }
   }

   return true;
#undef BUFSZ
}