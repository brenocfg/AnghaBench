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
typedef  int retro_time_t ;
struct TYPE_3__ {int quick_tap_time; } ;
typedef  TYPE_1__ android_input_t ;

/* Variables and functions */
 int cpu_features_get_time_usec () ; 

__attribute__((used)) static int android_check_quick_tap(android_input_t *android)
{
   /* Check if the touch screen has been been quick tapped
    * and then not touched again for 200ms
    * If so then return true and deactivate quick tap timer */
   retro_time_t now = cpu_features_get_time_usec();
   if (android->quick_tap_time && (now/1000 - android->quick_tap_time/1000000) >= 200)
   {
      android->quick_tap_time = 0;
      return 1;
   }

   return 0;
}