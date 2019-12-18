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

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ ix86_save_reg (int,int) ; 

__attribute__((used)) static int
ix86_nsaved_regs (void)
{
  int nregs = 0;
  int regno;

  for (regno = FIRST_PSEUDO_REGISTER - 1; regno >= 0; regno--)
    if (ix86_save_reg (regno, true))
      nregs++;
  return nregs;
}