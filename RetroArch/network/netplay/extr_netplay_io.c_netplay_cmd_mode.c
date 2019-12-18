#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct netplay_connection {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * netplay_request_devices; } ;
struct TYPE_9__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_10__ {scalar_t__ is_server; struct netplay_connection one_connection; } ;
typedef  TYPE_3__ netplay_t ;
typedef  enum rarch_netplay_connection_mode { ____Placeholder_rarch_netplay_connection_mode } rarch_netplay_connection_mode ;

/* Variables and functions */
 int MAX_INPUT_DEVICES ; 
 int NETPLAY_CMD_PLAY ; 
 int NETPLAY_CMD_PLAY_BIT_SLAVE ; 
 int NETPLAY_CMD_SPECTATE ; 
#define  NETPLAY_CONNECTION_PLAYING 130 
#define  NETPLAY_CONNECTION_SLAVE 129 
#define  NETPLAY_CONNECTION_SPECTATING 128 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  handle_play_spectate (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int*) ; 
 int htonl (int) ; 
 int netplay_send_raw_cmd (TYPE_3__*,struct netplay_connection*,int,int*,int) ; 
 int /*<<< orphan*/  netplay_settings_share_mode () ; 

bool netplay_cmd_mode(netplay_t *netplay,
   enum rarch_netplay_connection_mode mode)
{
   uint32_t cmd, device;
   uint32_t payloadBuf = 0, *payload = NULL;
   uint8_t share_mode;
   settings_t *settings = config_get_ptr();
   struct netplay_connection *connection = NULL;

   if (!netplay->is_server)
      connection = &netplay->one_connection;

   switch (mode)
   {
      case NETPLAY_CONNECTION_SPECTATING:
         cmd = NETPLAY_CMD_SPECTATE;
         break;

      case NETPLAY_CONNECTION_SLAVE:
         payloadBuf = NETPLAY_CMD_PLAY_BIT_SLAVE;
         /* no break */

      case NETPLAY_CONNECTION_PLAYING:
         payload = &payloadBuf;

         /* Add a share mode if requested */
         share_mode = netplay_settings_share_mode();
         payloadBuf |= ((uint32_t) share_mode) << 16;

         /* Request devices */
         for (device = 0; device < MAX_INPUT_DEVICES; device++)
         {
            if (settings->bools.netplay_request_devices[device])
               payloadBuf |= 1<<device;
         }

         payloadBuf = htonl(payloadBuf);
         cmd = NETPLAY_CMD_PLAY;
         break;

      default:
         return false;
   }

   if (netplay->is_server)
   {
      handle_play_spectate(netplay, 0, NULL, cmd, payload ? sizeof(uint32_t) : 0, payload);
      return true;

   }
   else
   {
      return netplay_send_raw_cmd(netplay, connection, cmd, payload,
            payload ? sizeof(uint32_t) : 0);
   }
}