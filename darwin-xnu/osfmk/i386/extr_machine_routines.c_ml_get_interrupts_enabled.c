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
typedef  int boolean_t ;

/* Variables and functions */
 unsigned long EFL_IF ; 

boolean_t ml_get_interrupts_enabled(void)
{
  unsigned long flags;

  __asm__ volatile("pushf; pop	%0" :  "=r" (flags));
  return (flags & EFL_IF) != 0;
}