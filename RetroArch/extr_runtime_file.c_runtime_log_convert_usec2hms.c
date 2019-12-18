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
typedef  int retro_time_t ;

/* Variables and functions */

void runtime_log_convert_usec2hms(retro_time_t usec,
      unsigned *hours, unsigned *minutes, unsigned *seconds)
{
   *seconds  = (unsigned)(usec / 1000000);
   *minutes  = *seconds / 60;
   *hours    = *minutes / 60;
   
   *seconds -= *minutes * 60;
   *minutes -= *hours * 60;
}