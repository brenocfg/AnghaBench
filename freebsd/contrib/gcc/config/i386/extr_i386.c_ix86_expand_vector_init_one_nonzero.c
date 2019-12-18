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
 int /*<<< orphan*/  CONST0_RTX (int) ; 
 int /*<<< orphan*/  FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GET_MODE_INNER (int) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  TARGET_SSE2 ; 
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
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  convert_modes (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_lowpart (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int const) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_CONCAT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_DUPLICATE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_MERGE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_pshufd_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_shufps_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ix86_expand_vector_init_one_nonzero (bool mmx_ok, enum machine_mode mode,
				     rtx target, rtx var, int one_var)
{
  enum machine_mode vsimode;
  rtx new_target;
  rtx x, tmp;

  switch (mode)
    {
    case V2SFmode:
    case V2SImode:
      if (!mmx_ok)
	return false;
      /* FALLTHRU */

    case V2DFmode:
    case V2DImode:
      if (one_var != 0)
	return false;
      var = force_reg (GET_MODE_INNER (mode), var);
      x = gen_rtx_VEC_CONCAT (mode, var, CONST0_RTX (GET_MODE_INNER (mode)));
      emit_insn (gen_rtx_SET (VOIDmode, target, x));
      return true;

    case V4SFmode:
    case V4SImode:
      if (!REG_P (target) || REGNO (target) < FIRST_PSEUDO_REGISTER)
	new_target = gen_reg_rtx (mode);
      else
	new_target = target;
      var = force_reg (GET_MODE_INNER (mode), var);
      x = gen_rtx_VEC_DUPLICATE (mode, var);
      x = gen_rtx_VEC_MERGE (mode, x, CONST0_RTX (mode), const1_rtx);
      emit_insn (gen_rtx_SET (VOIDmode, new_target, x));
      if (one_var != 0)
	{
	  /* We need to shuffle the value to the correct position, so
	     create a new pseudo to store the intermediate result.  */

	  /* With SSE2, we can use the integer shuffle insns.  */
	  if (mode != V4SFmode && TARGET_SSE2)
	    {
	      emit_insn (gen_sse2_pshufd_1 (new_target, new_target,
					    GEN_INT (1),
					    GEN_INT (one_var == 1 ? 0 : 1),
					    GEN_INT (one_var == 2 ? 0 : 1),
					    GEN_INT (one_var == 3 ? 0 : 1)));
	      if (target != new_target)
		emit_move_insn (target, new_target);
	      return true;
	    }

	  /* Otherwise convert the intermediate result to V4SFmode and
	     use the SSE1 shuffle instructions.  */
	  if (mode != V4SFmode)
	    {
	      tmp = gen_reg_rtx (V4SFmode);
	      emit_move_insn (tmp, gen_lowpart (V4SFmode, new_target));
	    }
	  else
	    tmp = new_target;

	  emit_insn (gen_sse_shufps_1 (tmp, tmp, tmp,
				       GEN_INT (1),
				       GEN_INT (one_var == 1 ? 0 : 1),
				       GEN_INT (one_var == 2 ? 0+4 : 1+4),
				       GEN_INT (one_var == 3 ? 0+4 : 1+4)));

	  if (mode != V4SFmode)
	    emit_move_insn (target, gen_lowpart (V4SImode, tmp));
	  else if (tmp != target)
	    emit_move_insn (target, tmp);
	}
      else if (target != new_target)
	emit_move_insn (target, new_target);
      return true;

    case V8HImode:
    case V16QImode:
      vsimode = V4SImode;
      goto widen;
    case V4HImode:
    case V8QImode:
      if (!mmx_ok)
	return false;
      vsimode = V2SImode;
      goto widen;
    widen:
      if (one_var != 0)
	return false;

      /* Zero extend the variable element to SImode and recurse.  */
      var = convert_modes (SImode, GET_MODE_INNER (mode), var, true);

      x = gen_reg_rtx (vsimode);
      if (!ix86_expand_vector_init_one_nonzero (mmx_ok, vsimode, x,
						var, one_var))
	gcc_unreachable ();

      emit_move_insn (target, gen_lowpart (mode, x));
      return true;

    default:
      return false;
    }
}