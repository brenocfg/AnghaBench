#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {TYPE_2__* sec_joypad; TYPE_1__* joypad; } ;
typedef  TYPE_3__ cocoa_input_data_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* poll ) () ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* poll ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  apple_keyboard_find_any_key () ; 
 scalar_t__ input_driver_get_data () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

int32_t cocoa_input_find_any_key(void)
{
   cocoa_input_data_t *apple = (cocoa_input_data_t*)input_driver_get_data();

   if (!apple)
      return 0;

   if (apple->joypad)
       apple->joypad->poll();

    if (apple->sec_joypad)
        apple->sec_joypad->poll();

   return apple_keyboard_find_any_key();
}