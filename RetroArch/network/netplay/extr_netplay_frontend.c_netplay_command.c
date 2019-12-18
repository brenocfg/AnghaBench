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
typedef  enum netplay_cmd { ____Placeholder_netplay_cmd } netplay_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  netplay_send_raw_cmd (int /*<<< orphan*/ *,struct netplay_connection*,int,void*,size_t) ; 
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char const*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool netplay_command(netplay_t* netplay, struct netplay_connection *connection,
   enum netplay_cmd cmd, void* data, size_t sz, const char* command_str,
   const char* success_msg)
{
   retro_assert(netplay);

   if (!netplay_send_raw_cmd(netplay, connection, cmd, data, sz))
      return false;

   runloop_msg_queue_push(success_msg, 1, 180, false, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

   return true;
}