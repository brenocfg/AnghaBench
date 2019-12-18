#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* state_cb ) (unsigned int,unsigned int,unsigned int,unsigned int) ;} ;
struct TYPE_7__ {TYPE_1__ cbs; } ;
typedef  TYPE_2__ netplay_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 TYPE_2__* netplay_data ; 
 int /*<<< orphan*/  netplay_input_state (TYPE_2__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ netplay_is_alive (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int,unsigned int,unsigned int) ; 

int16_t input_state_net(unsigned port, unsigned device,
      unsigned idx, unsigned id)
{
   netplay_t *netplay = netplay_data;
   if (netplay_is_alive(netplay))
      return netplay_input_state(netplay, port, device, idx, id);
   return netplay->cbs.state_cb(port, device, idx, id);
}