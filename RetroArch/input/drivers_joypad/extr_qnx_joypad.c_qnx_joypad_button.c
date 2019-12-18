#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ * devices; } ;
typedef  TYPE_1__ qnx_input_t ;
struct TYPE_4__ {int buttons; } ;
typedef  TYPE_2__ qnx_input_device_t ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 unsigned int MAX_USERS ; 
 scalar_t__ input_driver_get_data () ; 

__attribute__((used)) static bool qnx_joypad_button(unsigned port_num, uint16_t joykey)
{
   qnx_input_device_t* controller = NULL;
   qnx_input_t *qnx              = (qnx_input_t*)input_driver_get_data();

   if (!qnx || port_num >= DEFAULT_MAX_PADS)
      return 0;

   controller = (qnx_input_device_t*)&qnx->devices[port_num];

   if(port_num < MAX_USERS && joykey <= 19)
      return (controller->buttons & (1 << joykey)) != 0;

   return false;
}