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
typedef  int /*<<< orphan*/  input_device_driver_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
 int /*<<< orphan*/ ** pad_drivers ; 

__attribute__((used)) static void wiiu_joypad_connection_listener(unsigned pad,
               input_device_driver_t *driver)
{
   if (pad < MAX_USERS)
      pad_drivers[pad] = driver;
}