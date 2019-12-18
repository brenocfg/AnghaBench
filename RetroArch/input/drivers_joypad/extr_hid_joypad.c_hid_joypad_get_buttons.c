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
typedef  int /*<<< orphan*/  input_bits_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_buttons ) (void*,unsigned int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL_PTR (int /*<<< orphan*/ *) ; 
 TYPE_1__* generic_hid ; 
 scalar_t__ hid_driver_get_data () ; 
 int /*<<< orphan*/  stub1 (void*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hid_joypad_get_buttons(unsigned port, input_bits_t *state)
{
   if (generic_hid && generic_hid->get_buttons)
      generic_hid->get_buttons((void*)hid_driver_get_data(), port, state);
   else
      BIT256_CLEAR_ALL_PTR(state);
}