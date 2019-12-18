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
struct netplay_host_list {size_t size; struct netplay_host* hosts; } ;
struct netplay_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NETPLAY_DEINIT ; 
 int /*<<< orphan*/  CMD_EVENT_NETPLAY_INIT_DIRECT ; 
 int /*<<< orphan*/  CMD_EVENT_RESUME ; 
 int /*<<< orphan*/  RARCH_NETPLAY_CTL_ENABLE_CLIENT ; 
 int /*<<< orphan*/  RARCH_NETPLAY_CTL_IS_DATA_INITED ; 
 int /*<<< orphan*/  RARCH_NETPLAY_DISCOVERY_CTL_LAN_GET_RESPONSES ; 
 scalar_t__ command_event (int /*<<< orphan*/ ,void*) ; 
 int generic_action_ok_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netplay_discovery_driver_ctl (int /*<<< orphan*/ ,struct netplay_host_list**) ; 
 scalar_t__ netplay_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_ok_netplay_lan_scan(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
#ifdef HAVE_NETWORKING
   struct netplay_host_list *hosts = NULL;
   struct netplay_host *host       = NULL;

   /* Figure out what host we're connecting to */
   if (!netplay_discovery_driver_ctl(RARCH_NETPLAY_DISCOVERY_CTL_LAN_GET_RESPONSES, &hosts))
      return -1;
   if (entry_idx >= hosts->size)
      return -1;
   host = &hosts->hosts[entry_idx];

   /* Enable Netplay client mode */
   if (netplay_driver_ctl(RARCH_NETPLAY_CTL_IS_DATA_INITED, NULL))
      generic_action_ok_command(CMD_EVENT_NETPLAY_DEINIT);
   netplay_driver_ctl(RARCH_NETPLAY_CTL_ENABLE_CLIENT, NULL);

   /* Enable Netplay */
   if (command_event(CMD_EVENT_NETPLAY_INIT_DIRECT, (void *) host))
      return generic_action_ok_command(CMD_EVENT_RESUME);
#endif
   return -1;
}