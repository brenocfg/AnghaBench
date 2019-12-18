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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ active_insn_p (scalar_t__) ; 

rtx
next_active_insn (rtx insn)
{
  while (insn)
    {
      insn = NEXT_INSN (insn);
      if (insn == 0 || active_insn_p (insn))
	break;
    }

  return insn;
}