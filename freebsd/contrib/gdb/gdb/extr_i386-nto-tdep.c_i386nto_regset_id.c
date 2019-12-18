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
 int FP0_REGNUM ; 
 int FPC_REGNUM ; 
 int NTO_REG_END ; 
 int NTO_REG_FLOAT ; 
 int NTO_REG_GENERAL ; 

__attribute__((used)) static int
i386nto_regset_id (int regno)
{
  if (regno == -1)
    return NTO_REG_END;
  else if (regno < FP0_REGNUM)
    return NTO_REG_GENERAL;
  else if (regno < FPC_REGNUM)
    return NTO_REG_FLOAT;

  return -1;			/* Error.  */
}