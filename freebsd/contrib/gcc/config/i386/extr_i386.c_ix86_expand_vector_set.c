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
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_INNER (int) ; 
 int GET_MODE_SIZE (int) ; 
 int const SFmode ; 
 int /*<<< orphan*/  TARGET_3DNOW_A ; 
 int /*<<< orphan*/  TARGET_SSE ; 
 int TARGET_SSE2 ; 
#define  V16QImode 137 
#define  V2DFmode 136 
#define  V2DImode 135 
#define  V2SFmode 134 
#define  V2SImode 133 
#define  V4HImode 132 
#define  V4SFmode 131 
#define  V4SImode 130 
#define  V8HImode 129 
#define  V8QImode 128 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assign_stack_temp (int,int,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  const2_rtx ; 
 int /*<<< orphan*/  copy_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_lowpart (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_CONCAT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_DUPLICATE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_MERGE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_SELECT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_pshufd_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_shufps_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_unpcklps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_expand_vector_extract (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ix86_expand_vector_set (bool mmx_ok, rtx target, rtx val, int elt)
{
  enum machine_mode mode = GET_MODE (target);
  enum machine_mode inner_mode = GET_MODE_INNER (mode);
  bool use_vec_merge = false;
  rtx tmp;

  switch (mode)
    {
    case V2SFmode:
    case V2SImode:
      if (mmx_ok)
	{
	  tmp = gen_reg_rtx (GET_MODE_INNER (mode));
	  ix86_expand_vector_extract (true, tmp, target, 1 - elt);
	  if (elt == 0)
	    tmp = gen_rtx_VEC_CONCAT (mode, tmp, val);
	  else
	    tmp = gen_rtx_VEC_CONCAT (mode, val, tmp);
	  emit_insn (gen_rtx_SET (VOIDmode, target, tmp));
	  return;
	}
      break;

    case V2DFmode:
    case V2DImode:
      {
	rtx op0, op1;

	/* For the two element vectors, we implement a VEC_CONCAT with
	   the extraction of the other element.  */

	tmp = gen_rtx_PARALLEL (VOIDmode, gen_rtvec (1, GEN_INT (1 - elt)));
	tmp = gen_rtx_VEC_SELECT (inner_mode, target, tmp);

	if (elt == 0)
	  op0 = val, op1 = tmp;
	else
	  op0 = tmp, op1 = val;

	tmp = gen_rtx_VEC_CONCAT (mode, op0, op1);
	emit_insn (gen_rtx_SET (VOIDmode, target, tmp));
      }
      return;

    case V4SFmode:
      switch (elt)
	{
	case 0:
	  use_vec_merge = true;
	  break;

	case 1:
	  /* tmp = target = A B C D */
	  tmp = copy_to_reg (target);
	  /* target = A A B B */
	  emit_insn (gen_sse_unpcklps (target, target, target));
	  /* target = X A B B */
	  ix86_expand_vector_set (false, target, val, 0);
	  /* target = A X C D  */
	  emit_insn (gen_sse_shufps_1 (target, target, tmp,
				       GEN_INT (1), GEN_INT (0),
				       GEN_INT (2+4), GEN_INT (3+4)));
	  return;

	case 2:
	  /* tmp = target = A B C D */
	  tmp = copy_to_reg (target);
	  /* tmp = X B C D */
	  ix86_expand_vector_set (false, tmp, val, 0);
	  /* target = A B X D */
	  emit_insn (gen_sse_shufps_1 (target, target, tmp,
				       GEN_INT (0), GEN_INT (1),
				       GEN_INT (0+4), GEN_INT (3+4)));
	  return;

	case 3:
	  /* tmp = target = A B C D */
	  tmp = copy_to_reg (target);
	  /* tmp = X B C D */
	  ix86_expand_vector_set (false, tmp, val, 0);
	  /* target = A B X D */
	  emit_insn (gen_sse_shufps_1 (target, target, tmp,
				       GEN_INT (0), GEN_INT (1),
				       GEN_INT (2+4), GEN_INT (0+4)));
	  return;

	default:
	  gcc_unreachable ();
	}
      break;

    case V4SImode:
      /* Element 0 handled by vec_merge below.  */
      if (elt == 0)
	{
	  use_vec_merge = true;
	  break;
	}

      if (TARGET_SSE2)
	{
	  /* With SSE2, use integer shuffles to swap element 0 and ELT,
	     store into element 0, then shuffle them back.  */

	  rtx order[4];

	  order[0] = GEN_INT (elt);
	  order[1] = const1_rtx;
	  order[2] = const2_rtx;
	  order[3] = GEN_INT (3);
	  order[elt] = const0_rtx;

	  emit_insn (gen_sse2_pshufd_1 (target, target, order[0],
					order[1], order[2], order[3]));

	  ix86_expand_vector_set (false, target, val, 0);

	  emit_insn (gen_sse2_pshufd_1 (target, target, order[0],
					order[1], order[2], order[3]));
	}
      else
	{
	  /* For SSE1, we have to reuse the V4SF code.  */
	  ix86_expand_vector_set (false, gen_lowpart (V4SFmode, target),
				  gen_lowpart (SFmode, val), elt);
	}
      return;

    case V8HImode:
      use_vec_merge = TARGET_SSE2;
      break;
    case V4HImode:
      use_vec_merge = mmx_ok && (TARGET_SSE || TARGET_3DNOW_A);
      break;

    case V16QImode:
    case V8QImode:
    default:
      break;
    }

  if (use_vec_merge)
    {
      tmp = gen_rtx_VEC_DUPLICATE (mode, val);
      tmp = gen_rtx_VEC_MERGE (mode, tmp, target, GEN_INT (1 << elt));
      emit_insn (gen_rtx_SET (VOIDmode, target, tmp));
    }
  else
    {
      rtx mem = assign_stack_temp (mode, GET_MODE_SIZE (mode), false);

      emit_move_insn (mem, target);

      tmp = adjust_address (mem, inner_mode, elt*GET_MODE_SIZE (inner_mode));
      emit_move_insn (tmp, val);

      emit_move_insn (target, mem);
    }
}