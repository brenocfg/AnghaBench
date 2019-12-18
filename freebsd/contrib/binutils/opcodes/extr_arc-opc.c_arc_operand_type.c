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
 int AUXREG ; 
 int COND ; 
 int REG ; 

int
arc_operand_type (int opertype)
{
  switch (opertype)
    {
    case 0:
      return COND;
      break;
    case 1:
      return REG;
      break;
    case 2:
      return AUXREG;
      break;
    }
  return -1;
}