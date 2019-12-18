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
typedef  int /*<<< orphan*/  retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_NETPLAY_DISCOVERY_CTL_LAN_CLEAR_RESPONSES ; 
 int /*<<< orphan*/  RARCH_NETPLAY_DISCOVERY_CTL_LAN_SEND_QUERY ; 
 scalar_t__ init_netplay_discovery () ; 
 int /*<<< orphan*/  netplay_discovery_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_finished (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  task_set_progress (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void task_netplay_lan_scan_handler(retro_task_t *task)
{
   if (init_netplay_discovery())
   {
      netplay_discovery_driver_ctl(
            RARCH_NETPLAY_DISCOVERY_CTL_LAN_CLEAR_RESPONSES, NULL);
      netplay_discovery_driver_ctl(
            RARCH_NETPLAY_DISCOVERY_CTL_LAN_SEND_QUERY, NULL);
   }

   task_set_progress(task, 100);
   task_set_finished(task, true);

   return;
}