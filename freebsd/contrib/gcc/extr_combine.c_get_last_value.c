#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
struct TYPE_10__ {TYPE_3__* next_bb; } ;
struct TYPE_9__ {scalar_t__ last_set_value; scalar_t__ last_set_label; int /*<<< orphan*/  last_set; } ;
struct TYPE_7__ {TYPE_1__* rtl; } ;
struct TYPE_8__ {TYPE_2__ il; } ;
struct TYPE_6__ {int /*<<< orphan*/  global_live_at_start; } ;

/* Variables and functions */
 TYPE_5__* ENTRY_BLOCK_PTR ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_CUID (int /*<<< orphan*/ ) ; 
 unsigned int REGNO (scalar_t__) ; 
 scalar_t__ REGNO_REG_SET_P (int /*<<< orphan*/ ,unsigned int) ; 
 int REG_N_SETS (unsigned int) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ copy_rtx (scalar_t__) ; 
 scalar_t__ gen_lowpart (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_last_value_validate (scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ label_tick ; 
 TYPE_4__* reg_stat ; 
 scalar_t__ subreg_lowpart_p (scalar_t__) ; 
 scalar_t__ subst_low_cuid ; 

__attribute__((used)) static rtx
get_last_value (rtx x)
{
  unsigned int regno;
  rtx value;

  /* If this is a non-paradoxical SUBREG, get the value of its operand and
     then convert it to the desired mode.  If this is a paradoxical SUBREG,
     we cannot predict what values the "extra" bits might have.  */
  if (GET_CODE (x) == SUBREG
      && subreg_lowpart_p (x)
      && (GET_MODE_SIZE (GET_MODE (x))
	  <= GET_MODE_SIZE (GET_MODE (SUBREG_REG (x))))
      && (value = get_last_value (SUBREG_REG (x))) != 0)
    return gen_lowpart (GET_MODE (x), value);

  if (!REG_P (x))
    return 0;

  regno = REGNO (x);
  value = reg_stat[regno].last_set_value;

  /* If we don't have a value, or if it isn't for this basic block and
     it's either a hard register, set more than once, or it's a live
     at the beginning of the function, return 0.

     Because if it's not live at the beginning of the function then the reg
     is always set before being used (is never used without being set).
     And, if it's set only once, and it's always set before use, then all
     uses must have the same last value, even if it's not from this basic
     block.  */

  if (value == 0
      || (reg_stat[regno].last_set_label != label_tick
	  && (regno < FIRST_PSEUDO_REGISTER
	      || REG_N_SETS (regno) != 1
	      || (REGNO_REG_SET_P
		  (ENTRY_BLOCK_PTR->next_bb->il.rtl->global_live_at_start,
		   regno)))))
    return 0;

  /* If the value was set in a later insn than the ones we are processing,
     we can't use it even if the register was only set once.  */
  if (INSN_CUID (reg_stat[regno].last_set) >= subst_low_cuid)
    return 0;

  /* If the value has all its registers valid, return it.  */
  if (get_last_value_validate (&value, reg_stat[regno].last_set,
			       reg_stat[regno].last_set_label, 0))
    return value;

  /* Otherwise, make a copy and replace any invalid register with
     (clobber (const_int 0)).  If that fails for some reason, return 0.  */

  value = copy_rtx (value);
  if (get_last_value_validate (&value, reg_stat[regno].last_set,
			       reg_stat[regno].last_set_label, 1))
    return value;

  return 0;
}