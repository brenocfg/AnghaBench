#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ self_mode; scalar_t__ is_replay; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 scalar_t__ NETPLAY_CONNECTION_CONNECTED ; 

__attribute__((used)) static bool netplay_should_skip(netplay_t *netplay)
{
   if (!netplay)
      return false;
   return netplay->is_replay && (netplay->self_mode >= NETPLAY_CONNECTION_CONNECTED);
}