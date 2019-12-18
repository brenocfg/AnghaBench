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
struct alignment_context {int /*<<< orphan*/  shift; int /*<<< orphan*/  modemaski; int /*<<< orphan*/  memsi; scalar_t__ aligned; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  AND ; 
 int /*<<< orphan*/  EQ ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 int /*<<< orphan*/  IOR ; 
 int /*<<< orphan*/  LSHIFTRT ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  convert_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_simple_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_alignment_context (struct alignment_context*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ register_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_emit_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_emit_compare_and_swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_emit_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_expand_mask_and_shift (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_bit_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
s390_expand_cs_hqi (enum machine_mode mode, rtx target, rtx mem, rtx cmp, rtx new)
{
  struct alignment_context ac;
  rtx cmpv, newv, val, resv, cc;
  rtx res = gen_reg_rtx (SImode);
  rtx csloop = gen_label_rtx ();
  rtx csend = gen_label_rtx ();

  gcc_assert (register_operand (target, VOIDmode));
  gcc_assert (MEM_P (mem));

  init_alignment_context (&ac, mem, mode);

  /* Shift the values to the correct bit positions.  */
  if (!(ac.aligned && MEM_P (cmp)))
    cmp = s390_expand_mask_and_shift (cmp, mode, ac.shift);
  if (!(ac.aligned && MEM_P (new)))
    new = s390_expand_mask_and_shift (new, mode, ac.shift);

  /* Load full word.  Subsequent loads are performed by CS.  */
  val = expand_simple_binop (SImode, AND, ac.memsi, ac.modemaski,
			     NULL_RTX, 1, OPTAB_DIRECT);

  /* Start CS loop.  */
  emit_label (csloop);
  /* val = "<mem>00..0<mem>" 
   * cmp = "00..0<cmp>00..0"
   * new = "00..0<new>00..0" 
   */

  /* Patch cmp and new with val at correct position.  */
  if (ac.aligned && MEM_P (cmp))
    {
      cmpv = force_reg (SImode, val);
      store_bit_field (cmpv, GET_MODE_BITSIZE (mode), 0, SImode, cmp);
    }
  else
    cmpv = force_reg (SImode, expand_simple_binop (SImode, IOR, cmp, val,
						   NULL_RTX, 1, OPTAB_DIRECT));
  if (ac.aligned && MEM_P (new))
    {
      newv = force_reg (SImode, val);
      store_bit_field (newv, GET_MODE_BITSIZE (mode), 0, SImode, new);
    }
  else
    newv = force_reg (SImode, expand_simple_binop (SImode, IOR, new, val,
						   NULL_RTX, 1, OPTAB_DIRECT));

  /* Jump to end if we're done (likely?).  */
  s390_emit_jump (csend, s390_emit_compare_and_swap (EQ, res, ac.memsi,
						     cmpv, newv));

  /* Check for changes outside mode.  */
  resv = expand_simple_binop (SImode, AND, res, ac.modemaski, 
			      NULL_RTX, 1, OPTAB_DIRECT);
  cc = s390_emit_compare (NE, resv, val); 
  emit_move_insn (val, resv);
  /* Loop internal if so.  */
  s390_emit_jump (csloop, cc);

  emit_label (csend);
  
  /* Return the correct part of the bitfield.  */
  convert_move (target, expand_simple_binop (SImode, LSHIFTRT, res, ac.shift, 
					     NULL_RTX, 1, OPTAB_DIRECT), 1);
}