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
struct TYPE_3__ {scalar_t__ fd; } ;

/* Variables and functions */
 int MAX_USERS ; 
 TYPE_1__* parport_pads ; 
 int /*<<< orphan*/  parport_poll_pad (TYPE_1__*) ; 

__attribute__((used)) static void parport_joypad_poll(void)
{
   int i;

   for (i = 0; i < MAX_USERS; i++)
   {
      if (parport_pads[i].fd >= 0)
         parport_poll_pad(&parport_pads[i]);
   }
}