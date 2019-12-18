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
typedef  int uint16_t ;

/* Variables and functions */
 int UINT64_C (int) ; 
 int button_state ; 
 int /*<<< orphan*/  wpad_query_pad (unsigned int) ; 

__attribute__((used)) static bool wpad_button(unsigned pad, uint16_t button_bit)
{
   if (!wpad_query_pad(pad))
      return false;

   return button_state & (UINT64_C(1) << button_bit);
}