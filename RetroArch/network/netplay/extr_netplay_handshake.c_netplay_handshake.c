#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct netplay_connection {int mode; } ;
typedef  int /*<<< orphan*/  netplay_t ;

/* Variables and functions */
 int NETPLAY_CONNECTION_CONNECTED ; 
#define  NETPLAY_CONNECTION_INIT 133 
#define  NETPLAY_CONNECTION_NONE 132 
#define  NETPLAY_CONNECTION_PRE_INFO 131 
#define  NETPLAY_CONNECTION_PRE_NICK 130 
#define  NETPLAY_CONNECTION_PRE_PASSWORD 129 
#define  NETPLAY_CONNECTION_PRE_SYNC 128 
 int netplay_handshake_init (int /*<<< orphan*/ *,struct netplay_connection*,int*) ; 
 int netplay_handshake_pre_info (int /*<<< orphan*/ *,struct netplay_connection*,int*) ; 
 int netplay_handshake_pre_nick (int /*<<< orphan*/ *,struct netplay_connection*,int*) ; 
 int netplay_handshake_pre_password (int /*<<< orphan*/ *,struct netplay_connection*,int*) ; 
 int netplay_handshake_pre_sync (int /*<<< orphan*/ *,struct netplay_connection*,int*) ; 
 int /*<<< orphan*/  netplay_send_cur_input (int /*<<< orphan*/ *,struct netplay_connection*) ; 

bool netplay_handshake(netplay_t *netplay,
   struct netplay_connection *connection, bool *had_input)
{
   bool ret = false;

   switch (connection->mode)
   {
      case NETPLAY_CONNECTION_INIT:
         ret = netplay_handshake_init(netplay, connection, had_input);
         break;
      case NETPLAY_CONNECTION_PRE_NICK:
         ret = netplay_handshake_pre_nick(netplay, connection, had_input);
         break;
      case NETPLAY_CONNECTION_PRE_PASSWORD:
         ret = netplay_handshake_pre_password(netplay, connection, had_input);
         break;
      case NETPLAY_CONNECTION_PRE_INFO:
         ret = netplay_handshake_pre_info(netplay, connection, had_input);
         break;
      case NETPLAY_CONNECTION_PRE_SYNC:
         ret = netplay_handshake_pre_sync(netplay, connection, had_input);
         break;
      case NETPLAY_CONNECTION_NONE:
      default:
         return false;
   }

   if (connection->mode >= NETPLAY_CONNECTION_CONNECTED &&
         !netplay_send_cur_input(netplay, connection))
      return false;

   return ret;
}