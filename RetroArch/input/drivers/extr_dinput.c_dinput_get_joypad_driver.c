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
struct dinput_input {int /*<<< orphan*/  const* joypad; } ;
typedef  int /*<<< orphan*/  input_device_driver_t ;

/* Variables and functions */

__attribute__((used)) static const input_device_driver_t *dinput_get_joypad_driver(void *data)
{
   struct dinput_input *di = (struct dinput_input*)data;
   if (!di)
      return NULL;
   return di->joypad;
}