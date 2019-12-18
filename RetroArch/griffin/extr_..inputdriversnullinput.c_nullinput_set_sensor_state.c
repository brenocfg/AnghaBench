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
typedef  enum retro_sensor_action { ____Placeholder_retro_sensor_action } retro_sensor_action ;

/* Variables and functions */

__attribute__((used)) static bool nullinput_set_sensor_state(void *data,
      unsigned port, enum retro_sensor_action action, unsigned event_rate)
{
   return false;
}