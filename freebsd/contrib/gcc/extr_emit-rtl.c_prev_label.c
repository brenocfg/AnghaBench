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
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 

rtx
prev_label (rtx insn)
{
  while (insn)
    {
      insn = PREV_INSN (insn);
      if (insn == 0 || LABEL_P (insn))
	break;
    }

  return insn;
}