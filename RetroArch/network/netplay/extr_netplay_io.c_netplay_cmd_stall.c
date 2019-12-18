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
typedef  int /*<<< orphan*/  uint32_t ;
struct netplay_connection {int dummy; } ;
typedef  int /*<<< orphan*/  netplay_t ;
typedef  int /*<<< orphan*/  frames ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_CMD_STALL ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int netplay_send_raw_cmd (int /*<<< orphan*/ *,struct netplay_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

bool netplay_cmd_stall(netplay_t *netplay,
   struct netplay_connection *connection,
   uint32_t frames)
{
   frames = htonl(frames);
   return netplay_send_raw_cmd(netplay, connection, NETPLAY_CMD_STALL, &frames, sizeof(frames));
}