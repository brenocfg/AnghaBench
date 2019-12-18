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
struct TYPE_2__ {int /*<<< orphan*/  (* poll ) (void*) ;} ;

/* Variables and functions */
 TYPE_1__* generic_hid ; 
 scalar_t__ hid_driver_get_data () ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void hid_joypad_poll(void)
{
   if (generic_hid && generic_hid->poll)
      generic_hid->poll((void*)hid_driver_get_data());
}