#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int /*<<< orphan*/  last_set_nonzero_bits; scalar_t__ last_set; } ;

/* Variables and functions */
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_BITSIZE (int) ; 
 int /*<<< orphan*/  GET_MODE_MASK (int) ; 
 scalar_t__ HOST_BITS_PER_WIDE_INT ; 
 scalar_t__ LOG_LINKS (scalar_t__) ; 
 unsigned int REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ SUBREG_PROMOTED_UNSIGNED_P (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 TYPE_1__* reg_stat ; 
 scalar_t__ single_set (scalar_t__) ; 

__attribute__((used)) static void
record_promoted_value (rtx insn, rtx subreg)
{
  rtx links, set;
  unsigned int regno = REGNO (SUBREG_REG (subreg));
  enum machine_mode mode = GET_MODE (subreg);

  if (GET_MODE_BITSIZE (mode) > HOST_BITS_PER_WIDE_INT)
    return;

  for (links = LOG_LINKS (insn); links;)
    {
      insn = XEXP (links, 0);
      set = single_set (insn);

      if (! set || !REG_P (SET_DEST (set))
	  || REGNO (SET_DEST (set)) != regno
	  || GET_MODE (SET_DEST (set)) != GET_MODE (SUBREG_REG (subreg)))
	{
	  links = XEXP (links, 1);
	  continue;
	}

      if (reg_stat[regno].last_set == insn)
	{
	  if (SUBREG_PROMOTED_UNSIGNED_P (subreg) > 0)
	    reg_stat[regno].last_set_nonzero_bits &= GET_MODE_MASK (mode);
	}

      if (REG_P (SET_SRC (set)))
	{
	  regno = REGNO (SET_SRC (set));
	  links = LOG_LINKS (insn);
	}
      else
	break;
    }
}