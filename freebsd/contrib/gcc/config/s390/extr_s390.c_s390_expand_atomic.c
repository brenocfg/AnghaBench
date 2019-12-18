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
struct alignment_context {scalar_t__ shift; int /*<<< orphan*/  memsi; scalar_t__ modemask; scalar_t__ modemaski; scalar_t__ aligned; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  AND 134 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
#define  IOR 133 
 int const LSHIFTRT ; 
 int MEM_P (scalar_t__) ; 
#define  MINUS 132 
#define  MULT 131 
 int /*<<< orphan*/  NE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
#define  PLUS 130 
#define  SET 129 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  VOIDmode ; 
#define  XOR 128 
 int /*<<< orphan*/  convert_move (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_simple_binop (int /*<<< orphan*/ ,int const,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ gen_label_rtx () ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_alignment_context (struct alignment_context*,scalar_t__,int) ; 
 scalar_t__ register_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_emit_compare_and_swap (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  s390_emit_jump (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ s390_expand_mask_and_shift (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  store_bit_field (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
s390_expand_atomic (enum machine_mode mode, enum rtx_code code,
		    rtx target, rtx mem, rtx val, bool after)
{
  struct alignment_context ac;
  rtx cmp;
  rtx new = gen_reg_rtx (SImode);
  rtx orig = gen_reg_rtx (SImode);
  rtx csloop = gen_label_rtx ();

  gcc_assert (!target || register_operand (target, VOIDmode));
  gcc_assert (MEM_P (mem));

  init_alignment_context (&ac, mem, mode);

  /* Shift val to the correct bit positions.
     Preserve "icm", but prevent "ex icm".  */
  if (!(ac.aligned && code == SET && MEM_P (val)))
    val = s390_expand_mask_and_shift (val, mode, ac.shift);

  /* Further preparation insns.  */
  if (code == PLUS || code == MINUS)
    emit_move_insn (orig, val);
  else if (code == MULT || code == AND) /* val = "11..1<val>11..1" */
    val = expand_simple_binop (SImode, XOR, val, ac.modemaski,
			       NULL_RTX, 1, OPTAB_DIRECT);

  /* Load full word.  Subsequent loads are performed by CS.  */
  cmp = force_reg (SImode, ac.memsi);

  /* Start CS loop.  */
  emit_label (csloop);
  emit_move_insn (new, cmp);

  /* Patch new with val at correct position.  */
  switch (code)
    {
    case PLUS:
    case MINUS:
      val = expand_simple_binop (SImode, code, new, orig,
				 NULL_RTX, 1, OPTAB_DIRECT);
      val = expand_simple_binop (SImode, AND, val, ac.modemask,
				 NULL_RTX, 1, OPTAB_DIRECT);
      /* FALLTHRU */
    case SET: 
      if (ac.aligned && MEM_P (val))
	store_bit_field (new, GET_MODE_BITSIZE (mode), 0, SImode, val);
      else
	{
	  new = expand_simple_binop (SImode, AND, new, ac.modemaski,
				     NULL_RTX, 1, OPTAB_DIRECT);
	  new = expand_simple_binop (SImode, IOR, new, val,
				     NULL_RTX, 1, OPTAB_DIRECT);
	}
      break;
    case AND:
    case IOR:
    case XOR:
      new = expand_simple_binop (SImode, code, new, val,
				 NULL_RTX, 1, OPTAB_DIRECT);
      break;
    case MULT: /* NAND */
      new = expand_simple_binop (SImode, XOR, new, ac.modemask,
				 NULL_RTX, 1, OPTAB_DIRECT);
      new = expand_simple_binop (SImode, AND, new, val,
				 NULL_RTX, 1, OPTAB_DIRECT);
      break;
    default:
      gcc_unreachable ();
    }

  s390_emit_jump (csloop, s390_emit_compare_and_swap (NE, cmp,
						      ac.memsi, cmp, new));

  /* Return the correct part of the bitfield.  */
  if (target)
    convert_move (target, expand_simple_binop (SImode, LSHIFTRT,
					       after ? new : cmp, ac.shift,
					       NULL_RTX, 1, OPTAB_DIRECT), 1);
}