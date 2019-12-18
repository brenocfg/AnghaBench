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
struct TYPE_5__ {scalar_t__ connections_size; int savestate_request_outstanding; TYPE_3__* connections; } ;
typedef  TYPE_1__ netplay_t ;
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_CMD_REQUEST_SAVESTATE ; 
 scalar_t__ NETPLAY_CONNECTION_CONNECTED ; 
 int netplay_send_raw_cmd (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool netplay_cmd_request_savestate(netplay_t *netplay)
{
   if (netplay->connections_size == 0 ||
       !netplay->connections[0].active ||
       netplay->connections[0].mode < NETPLAY_CONNECTION_CONNECTED)
      return false;
   if (netplay->savestate_request_outstanding)
      return true;
   netplay->savestate_request_outstanding = true;
   return netplay_send_raw_cmd(netplay, &netplay->connections[0],
      NETPLAY_CMD_REQUEST_SAVESTATE, NULL, 0);
}