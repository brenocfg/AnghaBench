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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/ * reg_known_value ; 
 unsigned int reg_known_value_size ; 

__attribute__((used)) static void
set_reg_known_value (unsigned int regno, rtx val)
{
  if (regno >= FIRST_PSEUDO_REGISTER)
    {
      regno -= FIRST_PSEUDO_REGISTER;
      if (regno < reg_known_value_size)
	reg_known_value[regno] = val;
    }
}