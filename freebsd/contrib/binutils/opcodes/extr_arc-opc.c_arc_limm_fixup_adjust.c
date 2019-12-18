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
typedef  int arc_insn ;

/* Variables and functions */
 int ARC_REG_LIMM ; 
 int ARC_REG_SHIMM ; 
 int B (int) ; 
 int C (int) ; 
 int I (int) ; 

int
arc_limm_fixup_adjust (arc_insn insn)
{
  int retval = 0;

  /* Check for st shimm,[limm].  */
  if ((insn & (I(-1) | C(-1) | B(-1))) ==
      (I(2) | C(ARC_REG_SHIMM) | B(ARC_REG_LIMM)))
    {
      retval = insn & 0x1ff;
      if (retval & 0x100) /* Sign extend 9 bit offset.  */
	retval |= ~0x1ff;
    }
  return -retval; /* Negate offset for return.  */
}