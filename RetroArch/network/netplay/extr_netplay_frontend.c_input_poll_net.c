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
typedef  int /*<<< orphan*/  netplay_t ;

/* Variables and functions */
 scalar_t__ netplay_can_poll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * netplay_data ; 
 int /*<<< orphan*/  netplay_poll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netplay_should_skip (int /*<<< orphan*/ *) ; 

void input_poll_net(void)
{
   netplay_t *netplay = netplay_data;
   if (!netplay_should_skip(netplay) && netplay_can_poll(netplay))
      netplay_poll(netplay);
}