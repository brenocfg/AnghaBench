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
struct TYPE_2__ {int /*<<< orphan*/  button_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_COPY16_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpad_query_pad (unsigned int) ; 
 int to_wiimote_channel (unsigned int) ; 
 TYPE_1__* wiimotes ; 

__attribute__((used)) static void kpad_get_buttons(unsigned pad, input_bits_t *state)
{
   int channel = to_wiimote_channel(pad);

   if (!kpad_query_pad(pad) || channel < 0)
      BIT256_CLEAR_ALL_PTR(state);
   else
      BITS_COPY16_PTR(state, wiimotes[channel].button_state);
}