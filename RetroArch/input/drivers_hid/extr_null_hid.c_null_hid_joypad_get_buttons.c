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

__attribute__((used)) static void null_hid_joypad_get_buttons(void *data,
      unsigned port, input_bits_t *state)
{
   (void)data;
   (void)port;

   BIT256_CLEAR_ALL_PTR(state);
}