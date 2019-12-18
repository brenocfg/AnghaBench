#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct delta_frame {int /*<<< orphan*/  crc; int /*<<< orphan*/  frame; } ;
typedef  int /*<<< orphan*/  payload ;
struct TYPE_5__ {size_t connections_size; TYPE_3__* connections; } ;
typedef  TYPE_1__ netplay_t ;
struct TYPE_6__ {scalar_t__ mode; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_CMD_CRC ; 
 scalar_t__ NETPLAY_CONNECTION_CONNECTED ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ netplay_send_raw_cmd (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

bool netplay_cmd_crc(netplay_t *netplay, struct delta_frame *delta)
{
   uint32_t payload[2];
   bool success = true;
   size_t i;
   payload[0] = htonl(delta->frame);
   payload[1] = htonl(delta->crc);
   for (i = 0; i < netplay->connections_size; i++)
   {
      if (netplay->connections[i].active &&
            netplay->connections[i].mode >= NETPLAY_CONNECTION_CONNECTED)
         success = netplay_send_raw_cmd(netplay, &netplay->connections[i],
            NETPLAY_CMD_CRC, payload, sizeof(payload)) && success;
   }
   return success;
}