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

/* Variables and functions */
 scalar_t__ video_context_driver_get_refresh_rate (float*) ; 

__attribute__((used)) static float gl_core_get_refresh_rate(void *data)
{
   float refresh_rate;
   if (video_context_driver_get_refresh_rate(&refresh_rate))
       return refresh_rate;
   return 0.0f;
}