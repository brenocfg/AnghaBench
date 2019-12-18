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
typedef  int /*<<< orphan*/ * rtx ;
typedef  int /*<<< orphan*/  rtvec ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ASHIFT ; 
 int /*<<< orphan*/ * GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 int GET_MODE_INNER (int) ; 
 int GET_MODE_NUNITS (int) ; 
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  IOR ; 
 int /*<<< orphan*/ * NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int /*<<< orphan*/  TARGET_SSE ; 
 int UNITS_PER_WORD ; 
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
 int /*<<< orphan*/ * XVECEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * convert_modes (int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * expand_simple_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * force_reg (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * gen_highpart (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_lowpart (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_reg_rtx (int const) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_rtvec_v (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_rtx_PARALLEL (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_CONCAT (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ix86_expand_vector_init (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_operand (int /*<<< orphan*/ *,int) ; 
 int word_mode ; 

__attribute__((used)) static void
ix86_expand_vector_init_general (bool mmx_ok, enum machine_mode mode,
				 rtx target, rtx vals)
{
  enum machine_mode half_mode = GET_MODE_INNER (mode);
  rtx op0 = NULL, op1 = NULL;
  bool use_vec_concat = false;

  switch (mode)
    {
    case V2SFmode:
    case V2SImode:
      if (!mmx_ok && !TARGET_SSE)
	break;
      /* FALLTHRU */

    case V2DFmode:
    case V2DImode:
      /* For the two element vectors, we always implement VEC_CONCAT.  */
      op0 = XVECEXP (vals, 0, 0);
      op1 = XVECEXP (vals, 0, 1);
      use_vec_concat = true;
      break;

    case V4SFmode:
      half_mode = V2SFmode;
      goto half;
    case V4SImode:
      half_mode = V2SImode;
      goto half;
    half:
      {
	rtvec v;

	/* For V4SF and V4SI, we implement a concat of two V2 vectors.
	   Recurse to load the two halves.  */

	op0 = gen_reg_rtx (half_mode);
	v = gen_rtvec (2, XVECEXP (vals, 0, 0), XVECEXP (vals, 0, 1));
	ix86_expand_vector_init (false, op0, gen_rtx_PARALLEL (half_mode, v));

	op1 = gen_reg_rtx (half_mode);
	v = gen_rtvec (2, XVECEXP (vals, 0, 2), XVECEXP (vals, 0, 3));
	ix86_expand_vector_init (false, op1, gen_rtx_PARALLEL (half_mode, v));

	use_vec_concat = true;
      }
      break;

    case V8HImode:
    case V16QImode:
    case V4HImode:
    case V8QImode:
      break;

    default:
      gcc_unreachable ();
    }

  if (use_vec_concat)
    {
      if (!register_operand (op0, half_mode))
	op0 = force_reg (half_mode, op0);
      if (!register_operand (op1, half_mode))
	op1 = force_reg (half_mode, op1);

      emit_insn (gen_rtx_SET (VOIDmode, target,
			      gen_rtx_VEC_CONCAT (mode, op0, op1)));
    }
  else
    {
      int i, j, n_elts, n_words, n_elt_per_word;
      enum machine_mode inner_mode;
      rtx words[4], shift;

      inner_mode = GET_MODE_INNER (mode);
      n_elts = GET_MODE_NUNITS (mode);
      n_words = GET_MODE_SIZE (mode) / UNITS_PER_WORD;
      n_elt_per_word = n_elts / n_words;
      shift = GEN_INT (GET_MODE_BITSIZE (inner_mode));

      for (i = 0; i < n_words; ++i)
	{
	  rtx word = NULL_RTX;

	  for (j = 0; j < n_elt_per_word; ++j)
	    {
	      rtx elt = XVECEXP (vals, 0, (i+1)*n_elt_per_word - j - 1);
	      elt = convert_modes (word_mode, inner_mode, elt, true);

	      if (j == 0)
		word = elt;
	      else
		{
		  word = expand_simple_binop (word_mode, ASHIFT, word, shift,
					      word, 1, OPTAB_LIB_WIDEN);
		  word = expand_simple_binop (word_mode, IOR, word, elt,
					      word, 1, OPTAB_LIB_WIDEN);
		}
	    }

	  words[i] = word;
	}

      if (n_words == 1)
	emit_move_insn (target, gen_lowpart (mode, words[0]));
      else if (n_words == 2)
	{
	  rtx tmp = gen_reg_rtx (mode);
	  emit_insn (gen_rtx_CLOBBER (VOIDmode, tmp));
	  emit_move_insn (gen_lowpart (word_mode, tmp), words[0]);
	  emit_move_insn (gen_highpart (word_mode, tmp), words[1]);
	  emit_move_insn (target, tmp);
	}
      else if (n_words == 4)
	{
	  rtx tmp = gen_reg_rtx (V4SImode);
	  vals = gen_rtx_PARALLEL (V4SImode, gen_rtvec_v (4, words));
	  ix86_expand_vector_init_general (false, V4SImode, tmp, vals);
	  emit_move_insn (target, gen_lowpart (mode, tmp));
	}
      else
	gcc_unreachable ();
    }
}