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
struct parport_joypad {int /*<<< orphan*/  buttons; } ;
typedef  int /*<<< orphan*/  input_bits_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_COPY16_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parport_pads ; 

__attribute__((used)) static void parport_joypad_get_buttons(unsigned port, input_bits_t *state)
{
	const struct parport_joypad *pad = (const struct parport_joypad*)
      &parport_pads[port];

	if (pad)
   {
		BITS_COPY16_PTR(state, pad->buttons);
	}
   else
		BIT256_CLEAR_ALL_PTR(state);
}