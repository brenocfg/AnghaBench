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
struct algorithm {int* op; int ops; int* log; } ;
typedef  scalar_t__ rtx ;
typedef  enum mult_variant { ____Placeholder_mult_variant } mult_variant ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_MASK (int) ; 
 int /*<<< orphan*/  LSHIFT_EXPR ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (scalar_t__) ; 
 int add_variant ; 
#define  alg_add_factor 134 
#define  alg_add_t2_m 133 
#define  alg_add_t_m2 132 
 int alg_m ; 
#define  alg_shift 131 
#define  alg_sub_factor 130 
#define  alg_sub_t2_m 129 
#define  alg_sub_t_m2 128 
 int alg_zero ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ copy_to_mode_reg (int,scalar_t__) ; 
 scalar_t__ expand_shift (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_unop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ force_operand (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ force_reg (int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ gen_lowpart (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_MINUS (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_MULT (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int,scalar_t__,scalar_t__) ; 
 scalar_t__ get_last_insn () ; 
 int /*<<< orphan*/  neg_optab ; 
 int negate_variant ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  set_unique_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_mult_const (enum machine_mode mode, rtx op0, HOST_WIDE_INT val,
		   rtx target, const struct algorithm *alg,
		   enum mult_variant variant)
{
  HOST_WIDE_INT val_so_far;
  rtx insn, accum, tem;
  int opno;
  enum machine_mode nmode;

  /* Avoid referencing memory over and over.
     For speed, but also for correctness when mem is volatile.  */
  if (MEM_P (op0))
    op0 = force_reg (mode, op0);

  /* ACCUM starts out either as OP0 or as a zero, depending on
     the first operation.  */

  if (alg->op[0] == alg_zero)
    {
      accum = copy_to_mode_reg (mode, const0_rtx);
      val_so_far = 0;
    }
  else if (alg->op[0] == alg_m)
    {
      accum = copy_to_mode_reg (mode, op0);
      val_so_far = 1;
    }
  else
    gcc_unreachable ();

  for (opno = 1; opno < alg->ops; opno++)
    {
      int log = alg->log[opno];
      rtx shift_subtarget = optimize ? 0 : accum;
      rtx add_target
	= (opno == alg->ops - 1 && target != 0 && variant != add_variant
	   && !optimize)
	  ? target : 0;
      rtx accum_target = optimize ? 0 : accum;

      switch (alg->op[opno])
	{
	case alg_shift:
	  accum = expand_shift (LSHIFT_EXPR, mode, accum,
				build_int_cst (NULL_TREE, log),
				NULL_RTX, 0);
	  val_so_far <<= log;
	  break;

	case alg_add_t_m2:
	  tem = expand_shift (LSHIFT_EXPR, mode, op0,
			      build_int_cst (NULL_TREE, log),
			      NULL_RTX, 0);
	  accum = force_operand (gen_rtx_PLUS (mode, accum, tem),
				 add_target ? add_target : accum_target);
	  val_so_far += (HOST_WIDE_INT) 1 << log;
	  break;

	case alg_sub_t_m2:
	  tem = expand_shift (LSHIFT_EXPR, mode, op0,
			      build_int_cst (NULL_TREE, log),
			      NULL_RTX, 0);
	  accum = force_operand (gen_rtx_MINUS (mode, accum, tem),
				 add_target ? add_target : accum_target);
	  val_so_far -= (HOST_WIDE_INT) 1 << log;
	  break;

	case alg_add_t2_m:
	  accum = expand_shift (LSHIFT_EXPR, mode, accum,
				build_int_cst (NULL_TREE, log),
				shift_subtarget,
				0);
	  accum = force_operand (gen_rtx_PLUS (mode, accum, op0),
				 add_target ? add_target : accum_target);
	  val_so_far = (val_so_far << log) + 1;
	  break;

	case alg_sub_t2_m:
	  accum = expand_shift (LSHIFT_EXPR, mode, accum,
				build_int_cst (NULL_TREE, log),
				shift_subtarget, 0);
	  accum = force_operand (gen_rtx_MINUS (mode, accum, op0),
				 add_target ? add_target : accum_target);
	  val_so_far = (val_so_far << log) - 1;
	  break;

	case alg_add_factor:
	  tem = expand_shift (LSHIFT_EXPR, mode, accum,
			      build_int_cst (NULL_TREE, log),
			      NULL_RTX, 0);
	  accum = force_operand (gen_rtx_PLUS (mode, accum, tem),
				 add_target ? add_target : accum_target);
	  val_so_far += val_so_far << log;
	  break;

	case alg_sub_factor:
	  tem = expand_shift (LSHIFT_EXPR, mode, accum,
			      build_int_cst (NULL_TREE, log),
			      NULL_RTX, 0);
	  accum = force_operand (gen_rtx_MINUS (mode, tem, accum),
				 (add_target
				  ? add_target : (optimize ? 0 : tem)));
	  val_so_far = (val_so_far << log) - val_so_far;
	  break;

	default:
	  gcc_unreachable ();
	}

      /* Write a REG_EQUAL note on the last insn so that we can cse
	 multiplication sequences.  Note that if ACCUM is a SUBREG,
	 we've set the inner register and must properly indicate
	 that.  */

      tem = op0, nmode = mode;
      if (GET_CODE (accum) == SUBREG)
	{
	  nmode = GET_MODE (SUBREG_REG (accum));
	  tem = gen_lowpart (nmode, op0);
	}

      insn = get_last_insn ();
      set_unique_reg_note (insn, REG_EQUAL,
			   gen_rtx_MULT (nmode, tem, GEN_INT (val_so_far)));
    }

  if (variant == negate_variant)
    {
      val_so_far = -val_so_far;
      accum = expand_unop (mode, neg_optab, accum, target, 0);
    }
  else if (variant == add_variant)
    {
      val_so_far = val_so_far + 1;
      accum = force_operand (gen_rtx_PLUS (mode, accum, op0), target);
    }

  /* Compare only the bits of val and val_so_far that are significant
     in the result mode, to avoid sign-/zero-extension confusion.  */
  val &= GET_MODE_MASK (mode);
  val_so_far &= GET_MODE_MASK (mode);
  gcc_assert (val == val_so_far);

  return accum;
}