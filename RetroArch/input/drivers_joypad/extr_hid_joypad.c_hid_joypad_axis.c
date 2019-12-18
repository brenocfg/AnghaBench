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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* axis ) (void*,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* generic_hid ; 
 scalar_t__ hid_driver_get_data () ; 
 int /*<<< orphan*/  stub1 (void*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int16_t hid_joypad_axis(unsigned port, uint32_t joyaxis)
{
   if (generic_hid && generic_hid->axis)
      return generic_hid->axis((void*)hid_driver_get_data(), port, joyaxis);
   return 0;
}