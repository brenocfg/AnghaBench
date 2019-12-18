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
struct TYPE_3__ {scalar_t__ iface; scalar_t__ connected; } ;
typedef  TYPE_1__ joypad_connection_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 

bool pad_connection_has_interface(joypad_connection_t *joyconn, unsigned pad)
{
   if (     joyconn && pad < MAX_USERS
         && joyconn[pad].connected
         && joyconn[pad].iface)
      return true;
   return false;
}