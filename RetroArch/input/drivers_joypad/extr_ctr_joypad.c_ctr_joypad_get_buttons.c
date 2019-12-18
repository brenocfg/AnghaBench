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
typedef  int /*<<< orphan*/  input_bits_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_COPY16_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int DEFAULT_MAX_PADS ; 
 int /*<<< orphan*/  pad_state ; 

__attribute__((used)) static void ctr_joypad_get_buttons(unsigned port_num, input_bits_t *state)
{
	if (port_num < DEFAULT_MAX_PADS)
   {
		BITS_COPY16_PTR( state, pad_state );
	}
   else
		BIT256_CLEAR_ALL_PTR(state);
}