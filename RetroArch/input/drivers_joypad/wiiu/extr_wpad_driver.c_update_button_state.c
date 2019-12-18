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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int VPAD_MASK_BUTTONS ; 

__attribute__((used)) static void update_button_state(uint64_t *state, uint32_t held_buttons)
{
   *state = held_buttons & VPAD_MASK_BUTTONS;
}