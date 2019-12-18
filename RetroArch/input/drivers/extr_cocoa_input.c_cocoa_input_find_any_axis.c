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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_6__ {TYPE_2__* sec_joypad; TYPE_1__* joypad; } ;
typedef  TYPE_3__ cocoa_input_data_t ;
struct TYPE_5__ {scalar_t__ (* axis ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* poll ) () ;} ;
struct TYPE_4__ {scalar_t__ (* axis ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* poll ) () ;} ;

/* Variables and functions */
 int abs (scalar_t__) ; 
 scalar_t__ input_driver_get_data () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,int) ; 

int32_t cocoa_input_find_any_axis(uint32_t port)
{
   int i;
   cocoa_input_data_t *apple = (cocoa_input_data_t*)input_driver_get_data();

   if (apple && apple->joypad)
       apple->joypad->poll();

   if (apple && apple->sec_joypad)
       apple->sec_joypad->poll();

   for (i = 0; i < 6; i++)
   {
      int16_t value = apple->joypad ? apple->joypad->axis(port, i) : 0;

      if (abs(value) > 0x4000)
         return (value < 0) ? -(i + 1) : i + 1;

      value = apple->sec_joypad ? apple->sec_joypad->axis(port, i) : value;

      if (abs(value) > 0x4000)
         return (value < 0) ? -(i + 1) : i + 1;
   }

   return 0;
}