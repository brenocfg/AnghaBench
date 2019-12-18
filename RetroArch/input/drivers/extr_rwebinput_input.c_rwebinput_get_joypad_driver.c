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
struct TYPE_2__ {int /*<<< orphan*/  const* joypad; } ;
typedef  TYPE_1__ rwebinput_input_t ;
typedef  int /*<<< orphan*/  input_device_driver_t ;

/* Variables and functions */

__attribute__((used)) static const input_device_driver_t *rwebinput_get_joypad_driver(void *data)
{
   rwebinput_input_t *rwebinput = (rwebinput_input_t*)data;
   if (!rwebinput)
      return NULL;
   return rwebinput->joypad;
}