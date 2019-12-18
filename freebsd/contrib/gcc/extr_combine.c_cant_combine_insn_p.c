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
 scalar_t__ CLASS_LIKELY_SPILLED_P (int /*<<< orphan*/ ) ; 
 size_t FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ ) ; 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO_REG_CLASS (size_t) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int /*<<< orphan*/  single_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cant_combine_insn_p (rtx insn)
{
  rtx set;
  rtx src, dest;

  /* If this isn't really an insn, we can't do anything.
     This can occur when flow deletes an insn that it has merged into an
     auto-increment address.  */
  if (! INSN_P (insn))
    return 1;

  /* Never combine loads and stores involving hard regs that are likely
     to be spilled.  The register allocator can usually handle such
     reg-reg moves by tying.  If we allow the combiner to make
     substitutions of likely-spilled regs, reload might die.
     As an exception, we allow combinations involving fixed regs; these are
     not available to the register allocator so there's no risk involved.  */

  set = single_set (insn);
  if (! set)
    return 0;
  src = SET_SRC (set);
  dest = SET_DEST (set);
  if (GET_CODE (src) == SUBREG)
    src = SUBREG_REG (src);
  if (GET_CODE (dest) == SUBREG)
    dest = SUBREG_REG (dest);
  if (REG_P (src) && REG_P (dest)
      && ((REGNO (src) < FIRST_PSEUDO_REGISTER
	   && ! fixed_regs[REGNO (src)]
	   && CLASS_LIKELY_SPILLED_P (REGNO_REG_CLASS (REGNO (src))))
	  || (REGNO (dest) < FIRST_PSEUDO_REGISTER
	      && ! fixed_regs[REGNO (dest)]
	      && CLASS_LIKELY_SPILLED_P (REGNO_REG_CLASS (REGNO (dest))))))
    return 1;

  return 0;
}