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
 int /*<<< orphan*/  BITS_COPY32_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  button_state ; 
 int /*<<< orphan*/  wpad_query_pad (unsigned int) ; 

__attribute__((used)) static void wpad_get_buttons(unsigned pad, input_bits_t *state)
{
   if (!wpad_query_pad(pad))
      BIT256_CLEAR_ALL_PTR(state);
   else
      BITS_COPY32_PTR(state, button_state);
}