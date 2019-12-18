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
struct TYPE_2__ {int State; scalar_t__ Timeout; scalar_t__ Counter; } ;

/* Variables and functions */
 TYPE_1__* gamepad ; 
 scalar_t__ pad_index ; 

void gamepad_reset(int port)
{
  /* default state (Gouketsuji Ichizoku / Power Instinct, Samurai Spirits / Samurai Shodown) */
  gamepad[port].State = 0x40;
  gamepad[port].Counter = 0;
  gamepad[port].Timeout = 0;

  /* reset pad index (4-WayPlay) */
  pad_index = 0;
}