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
 int HImode ; 
 int const SFmode ; 
 int const SImode ; 
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
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_lowpart (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_SELECT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_ZERO_EXTEND (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_pshufd_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_punpckhdq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_shufps_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_unpckhps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ix86_expand_vector_extract (bool mmx_ok, rtx target, rtx vec, int elt)
{
  enum machine_mode mode = GET_MODE (vec);
  enum machine_mode inner_mode = GET_MODE_INNER (mode);
  bool use_vec_extr = false;
  rtx tmp;

  switch (mode)
    {
    case V2SImode:
    case V2SFmode:
      if (!mmx_ok)
	break;
      /* FALLTHRU */

    case V2DFmode:
    case V2DImode:
      use_vec_extr = true;
      break;

    case V4SFmode:
      switch (elt)
	{
	case 0:
	  tmp = vec;
	  break;

	case 1:
	case 3:
	  tmp = gen_reg_rtx (mode);
	  emit_insn (gen_sse_shufps_1 (tmp, vec, vec,
				       GEN_INT (elt), GEN_INT (elt),
				       GEN_INT (elt+4), GEN_INT (elt+4)));
	  break;

	case 2:
	  tmp = gen_reg_rtx (mode);
	  emit_insn (gen_sse_unpckhps (tmp, vec, vec));
	  break;

	default:
	  gcc_unreachable ();
	}
      vec = tmp;
      use_vec_extr = true;
      elt = 0;
      break;

    case V4SImode:
      if (TARGET_SSE2)
	{
	  switch (elt)
	    {
	    case 0:
	      tmp = vec;
	      break;

	    case 1:
	    case 3:
	      tmp = gen_reg_rtx (mode);
	      emit_insn (gen_sse2_pshufd_1 (tmp, vec,
					    GEN_INT (elt), GEN_INT (elt),
					    GEN_INT (elt), GEN_INT (elt)));
	      break;

	    case 2:
	      tmp = gen_reg_rtx (mode);
	      emit_insn (gen_sse2_punpckhdq (tmp, vec, vec));
	      break;

	    default:
	      gcc_unreachable ();
	    }
	  vec = tmp;
	  use_vec_extr = true;
	  elt = 0;
	}
      else
	{
	  /* For SSE1, we have to reuse the V4SF code.  */
	  ix86_expand_vector_extract (false, gen_lowpart (SFmode, target),
				      gen_lowpart (V4SFmode, vec), elt);
	  return;
	}
      break;

    case V8HImode:
      use_vec_extr = TARGET_SSE2;
      break;
    case V4HImode:
      use_vec_extr = mmx_ok && (TARGET_SSE || TARGET_3DNOW_A);
      break;

    case V16QImode:
    case V8QImode:
      /* ??? Could extract the appropriate HImode element and shift.  */
    default:
      break;
    }

  if (use_vec_extr)
    {
      tmp = gen_rtx_PARALLEL (VOIDmode, gen_rtvec (1, GEN_INT (elt)));
      tmp = gen_rtx_VEC_SELECT (inner_mode, vec, tmp);

      /* Let the rtl optimizers know about the zero extension performed.  */
      if (inner_mode == HImode)
	{
	  tmp = gen_rtx_ZERO_EXTEND (SImode, tmp);
	  target = gen_lowpart (SImode, target);
	}

      emit_insn (gen_rtx_SET (VOIDmode, target, tmp));
    }
  else
    {
      rtx mem = assign_stack_temp (mode, GET_MODE_SIZE (mode), false);

      emit_move_insn (mem, vec);

      tmp = adjust_address (mem, inner_mode, elt*GET_MODE_SIZE (inner_mode));
      emit_move_insn (target, tmp);
    }
}