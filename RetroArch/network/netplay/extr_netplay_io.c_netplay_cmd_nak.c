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
struct netplay_connection {int dummy; } ;
typedef  int /*<<< orphan*/  netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_CMD_NAK ; 
 int /*<<< orphan*/  netplay_send_raw_cmd (int /*<<< orphan*/ *,struct netplay_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool netplay_cmd_nak(netplay_t *netplay,
   struct netplay_connection *connection)
{
   netplay_send_raw_cmd(netplay, connection, NETPLAY_CMD_NAK, NULL, 0);
   return false;
}