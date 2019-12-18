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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ALIAS_SET_MEMORY_BARRIER ; 
 scalar_t__ AND ; 
 scalar_t__ BLKmode ; 
 scalar_t__ DIFFERENT_ALIAS_SETS_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int) ; 
 scalar_t__ MEM_ALIAS_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_READONLY_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 int QImode ; 
 scalar_t__ SCRATCH ; 
 int /*<<< orphan*/  SIZE_FOR_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ aliases_everything_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_alias_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  canon_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_scalar_and_varying_struct_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (int /*<<< orphan*/ ,int)) ; 
 int /*<<< orphan*/  get_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memrefs_conflict_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nonoverlapping_memrefs_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
canon_true_dependence (rtx mem, enum machine_mode mem_mode, rtx mem_addr,
		       rtx x, int (*varies) (rtx, int))
{
  rtx x_addr;

  if (MEM_VOLATILE_P (x) && MEM_VOLATILE_P (mem))
    return 1;

  /* (mem:BLK (scratch)) is a special mechanism to conflict with everything.
     This is used in epilogue deallocation functions.  */
  if (GET_MODE (x) == BLKmode && GET_CODE (XEXP (x, 0)) == SCRATCH)
    return 1;
  if (GET_MODE (mem) == BLKmode && GET_CODE (XEXP (mem, 0)) == SCRATCH)
    return 1;
  if (MEM_ALIAS_SET (x) == ALIAS_SET_MEMORY_BARRIER
      || MEM_ALIAS_SET (mem) == ALIAS_SET_MEMORY_BARRIER)
    return 1;

  if (DIFFERENT_ALIAS_SETS_P (x, mem))
    return 0;

  /* Read-only memory is by definition never modified, and therefore can't
     conflict with anything.  We don't expect to find read-only set on MEM,
     but stupid user tricks can produce them, so don't die.  */
  if (MEM_READONLY_P (x))
    return 0;

  if (nonoverlapping_memrefs_p (x, mem))
    return 0;

  x_addr = get_addr (XEXP (x, 0));

  if (! base_alias_check (x_addr, mem_addr, GET_MODE (x), mem_mode))
    return 0;

  x_addr = canon_rtx (x_addr);
  if (! memrefs_conflict_p (GET_MODE_SIZE (mem_mode), mem_addr,
			    SIZE_FOR_MODE (x), x_addr, 0))
    return 0;

  if (aliases_everything_p (x))
    return 1;

  /* We cannot use aliases_everything_p to test MEM, since we must look
     at MEM_MODE, rather than GET_MODE (MEM).  */
  if (mem_mode == QImode || GET_CODE (mem_addr) == AND)
    return 1;

  /* In true_dependence we also allow BLKmode to alias anything.  Why
     don't we do this in anti_dependence and output_dependence?  */
  if (mem_mode == BLKmode || GET_MODE (x) == BLKmode)
    return 1;

  return ! fixed_scalar_and_varying_struct_p (mem, x, mem_addr, x_addr,
					      varies);
}