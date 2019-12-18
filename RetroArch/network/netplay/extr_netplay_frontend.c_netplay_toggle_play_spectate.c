#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ self_mode; } ;
typedef  TYPE_1__ netplay_t ;
typedef  enum rarch_netplay_connection_mode { ____Placeholder_rarch_netplay_connection_mode } rarch_netplay_connection_mode ;

/* Variables and functions */
 scalar_t__ NETPLAY_CONNECTION_PLAYING ; 
 scalar_t__ NETPLAY_CONNECTION_SLAVE ; 
 scalar_t__ NETPLAY_CONNECTION_SPECTATING ; 
 int /*<<< orphan*/  netplay_cmd_mode (TYPE_1__*,int) ; 

__attribute__((used)) static void netplay_toggle_play_spectate(netplay_t *netplay)
{
   enum rarch_netplay_connection_mode mode;

   if (netplay->self_mode == NETPLAY_CONNECTION_PLAYING ||
       netplay->self_mode == NETPLAY_CONNECTION_SLAVE)
   {
      /* Switch to spectator mode immediately */
      netplay->self_mode = NETPLAY_CONNECTION_SPECTATING;
      mode = NETPLAY_CONNECTION_SPECTATING;
   }
   else if (netplay->self_mode == NETPLAY_CONNECTION_SPECTATING)
   {
      /* Switch only after getting permission */
      mode = NETPLAY_CONNECTION_PLAYING;
   }
   else
      return;

   netplay_cmd_mode(netplay, mode);
}