#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp_hostname ;
struct TYPE_2__ {scalar_t__ host_method; char* mitm_address; int mitm_port; char* address; int port; int /*<<< orphan*/  subsystem_name; int /*<<< orphan*/  corename; int /*<<< orphan*/  gamename; int /*<<< orphan*/  gamecrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NETPLAY_DEINIT ; 
 scalar_t__ NETPLAY_HOST_METHOD_MITM ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_NETPLAY_CTL_ENABLE_CLIENT ; 
 int /*<<< orphan*/  RARCH_NETPLAY_CTL_IS_DATA_INITED ; 
 int /*<<< orphan*/  generic_action_ok_command (int /*<<< orphan*/ ) ; 
 scalar_t__ netplay_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* netplay_room_list ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  task_push_netplay_crc_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_ok_netplay_connect_room(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
#ifdef HAVE_NETWORKING
   char tmp_hostname[4115];

   tmp_hostname[0] = '\0';

   if (netplay_driver_ctl(RARCH_NETPLAY_CTL_IS_DATA_INITED, NULL))
      generic_action_ok_command(CMD_EVENT_NETPLAY_DEINIT);
   netplay_driver_ctl(RARCH_NETPLAY_CTL_ENABLE_CLIENT, NULL);

   if (netplay_room_list[idx - 3].host_method == NETPLAY_HOST_METHOD_MITM)
   {
      snprintf(tmp_hostname,
            sizeof(tmp_hostname),
            "%s|%d",
         netplay_room_list[idx - 3].mitm_address,
         netplay_room_list[idx - 3].mitm_port);
   }
   else
   {
      snprintf(tmp_hostname,
            sizeof(tmp_hostname),
            "%s|%d",
         netplay_room_list[idx - 3].address,
         netplay_room_list[idx - 3].port);
   }

#if 0
   RARCH_LOG("[lobby] connecting to: %s with game: %s/%08x\n",
         tmp_hostname,
         netplay_room_list[idx - 3].gamename,
         netplay_room_list[idx - 3].gamecrc);
#endif

   task_push_netplay_crc_scan(netplay_room_list[idx - 3].gamecrc,
      netplay_room_list[idx - 3].gamename,
      tmp_hostname, netplay_room_list[idx - 3].corename, netplay_room_list[idx - 3].subsystem_name);

#else
   return -1;

#endif
   return 0;
}