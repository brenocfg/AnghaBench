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
typedef  int /*<<< orphan*/  input_device_driver_t ;
struct TYPE_2__ {int /*<<< orphan*/  const* (* get_joypad_driver ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* current_input ; 
 int /*<<< orphan*/  current_input_data ; 
 int /*<<< orphan*/  const* stub1 (int /*<<< orphan*/ ) ; 

const input_device_driver_t *input_driver_get_joypad_driver(void)
{
   if (!current_input || !current_input->get_joypad_driver)
      return NULL;
   return current_input->get_joypad_driver(current_input_data);
}