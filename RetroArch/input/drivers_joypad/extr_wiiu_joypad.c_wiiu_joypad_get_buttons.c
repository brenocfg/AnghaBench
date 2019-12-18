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
struct TYPE_2__ {int /*<<< orphan*/  (* get_buttons ) (unsigned int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__** pad_drivers ; 
 int /*<<< orphan*/  stub1 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiu_joypad_query_pad (unsigned int) ; 

__attribute__((used)) static void wiiu_joypad_get_buttons(unsigned pad, input_bits_t *state)
{
   if (!wiiu_joypad_query_pad(pad))
      return;

   pad_drivers[pad]->get_buttons(pad, state);
}