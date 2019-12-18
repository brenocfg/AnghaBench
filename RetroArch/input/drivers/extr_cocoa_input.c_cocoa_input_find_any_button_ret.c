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
typedef  int /*<<< orphan*/  cocoa_input_data_t ;

/* Variables and functions */
 scalar_t__ BIT256_GET_PTR (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int cocoa_input_find_any_button_ret(cocoa_input_data_t *apple,
   input_bits_t * state, unsigned port)
{
   unsigned i;

   if (state)
      for (i = 0; i < 256; i++)
         if (BIT256_GET_PTR(state,i))
            return i;
   return -1;
}