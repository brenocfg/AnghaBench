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
 int /*<<< orphan*/  ASHIFT ; 
 int /*<<< orphan*/  CONST0_RTX (int const) ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 int /*<<< orphan*/  GET_MODE_INNER (int) ; 
 int HImode ; 
 int /*<<< orphan*/  IOR ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int QImode ; 
 int SImode ; 
 int /*<<< orphan*/  TARGET_3DNOW_A ; 
 int /*<<< orphan*/  TARGET_SSE ; 
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
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  convert_modes (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_simple_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_lowpart (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int const) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_TRUNCATE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_DUPLICATE (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_MERGE (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_pshufd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_punpcklbw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_punpcklwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ix86_expand_vector_init_duplicate (bool mmx_ok, enum machine_mode mode,
				   rtx target, rtx val)
{
  enum machine_mode smode, wsmode, wvmode;
  rtx x;

  switch (mode)
    {
    case V2SImode:
    case V2SFmode:
      if (!mmx_ok)
	return false;
      /* FALLTHRU */

    case V2DFmode:
    case V2DImode:
    case V4SFmode:
    case V4SImode:
      val = force_reg (GET_MODE_INNER (mode), val);
      x = gen_rtx_VEC_DUPLICATE (mode, val);
      emit_insn (gen_rtx_SET (VOIDmode, target, x));
      return true;

    case V4HImode:
      if (!mmx_ok)
	return false;
      if (TARGET_SSE || TARGET_3DNOW_A)
	{
	  val = gen_lowpart (SImode, val);
	  x = gen_rtx_TRUNCATE (HImode, val);
	  x = gen_rtx_VEC_DUPLICATE (mode, x);
	  emit_insn (gen_rtx_SET (VOIDmode, target, x));
	  return true;
	}
      else
	{
	  smode = HImode;
	  wsmode = SImode;
	  wvmode = V2SImode;
	  goto widen;
	}

    case V8QImode:
      if (!mmx_ok)
	return false;
      smode = QImode;
      wsmode = HImode;
      wvmode = V4HImode;
      goto widen;
    case V8HImode:
      if (TARGET_SSE2)
	{
	  rtx tmp1, tmp2;
	  /* Extend HImode to SImode using a paradoxical SUBREG.  */
	  tmp1 = gen_reg_rtx (SImode);
	  emit_move_insn (tmp1, gen_lowpart (SImode, val));
	  /* Insert the SImode value as low element of V4SImode vector. */
	  tmp2 = gen_reg_rtx (V4SImode);
	  tmp1 = gen_rtx_VEC_MERGE (V4SImode,
				    gen_rtx_VEC_DUPLICATE (V4SImode, tmp1),
				    CONST0_RTX (V4SImode),
				    const1_rtx);
	  emit_insn (gen_rtx_SET (VOIDmode, tmp2, tmp1));
	  /* Cast the V4SImode vector back to a V8HImode vector.  */
	  tmp1 = gen_reg_rtx (V8HImode);
	  emit_move_insn (tmp1, gen_lowpart (V8HImode, tmp2));
	  /* Duplicate the low short through the whole low SImode word.  */
	  emit_insn (gen_sse2_punpcklwd (tmp1, tmp1, tmp1));
	  /* Cast the V8HImode vector back to a V4SImode vector.  */
	  tmp2 = gen_reg_rtx (V4SImode);
	  emit_move_insn (tmp2, gen_lowpart (V4SImode, tmp1));
	  /* Replicate the low element of the V4SImode vector.  */
	  emit_insn (gen_sse2_pshufd (tmp2, tmp2, const0_rtx));
	  /* Cast the V2SImode back to V8HImode, and store in target.  */
	  emit_move_insn (target, gen_lowpart (V8HImode, tmp2));
	  return true;
	}
      smode = HImode;
      wsmode = SImode;
      wvmode = V4SImode;
      goto widen;
    case V16QImode:
      if (TARGET_SSE2)
	{
	  rtx tmp1, tmp2;
	  /* Extend QImode to SImode using a paradoxical SUBREG.  */
	  tmp1 = gen_reg_rtx (SImode);
	  emit_move_insn (tmp1, gen_lowpart (SImode, val));
	  /* Insert the SImode value as low element of V4SImode vector. */
	  tmp2 = gen_reg_rtx (V4SImode);
	  tmp1 = gen_rtx_VEC_MERGE (V4SImode,
				    gen_rtx_VEC_DUPLICATE (V4SImode, tmp1),
				    CONST0_RTX (V4SImode),
				    const1_rtx);
	  emit_insn (gen_rtx_SET (VOIDmode, tmp2, tmp1));
	  /* Cast the V4SImode vector back to a V16QImode vector.  */
	  tmp1 = gen_reg_rtx (V16QImode);
	  emit_move_insn (tmp1, gen_lowpart (V16QImode, tmp2));
	  /* Duplicate the low byte through the whole low SImode word.  */
	  emit_insn (gen_sse2_punpcklbw (tmp1, tmp1, tmp1));
	  emit_insn (gen_sse2_punpcklbw (tmp1, tmp1, tmp1));
	  /* Cast the V16QImode vector back to a V4SImode vector.  */
	  tmp2 = gen_reg_rtx (V4SImode);
	  emit_move_insn (tmp2, gen_lowpart (V4SImode, tmp1));
	  /* Replicate the low element of the V4SImode vector.  */
	  emit_insn (gen_sse2_pshufd (tmp2, tmp2, const0_rtx));
	  /* Cast the V2SImode back to V16QImode, and store in target.  */
	  emit_move_insn (target, gen_lowpart (V16QImode, tmp2));
	  return true;
	}
      smode = QImode;
      wsmode = HImode;
      wvmode = V8HImode;
      goto widen;
    widen:
      /* Replicate the value once into the next wider mode and recurse.  */
      val = convert_modes (wsmode, smode, val, true);
      x = expand_simple_binop (wsmode, ASHIFT, val,
			       GEN_INT (GET_MODE_BITSIZE (smode)),
			       NULL_RTX, 1, OPTAB_LIB_WIDEN);
      val = expand_simple_binop (wsmode, IOR, val, x, x, 1, OPTAB_LIB_WIDEN);

      x = gen_reg_rtx (wvmode);
      if (!ix86_expand_vector_init_duplicate (mmx_ok, wvmode, x, val))
	gcc_unreachable ();
      emit_move_insn (target, gen_lowpart (mode, x));
      return true;

    default:
      return false;
    }
}