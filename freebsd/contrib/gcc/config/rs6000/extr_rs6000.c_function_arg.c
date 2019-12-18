#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  scalar_t__ rtx ;
typedef  enum rs6000_abi { ____Placeholder_rs6000_abi } rs6000_abi ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_7__ {int call_cookie; scalar_t__ nargs_prototype; scalar_t__ fregno; int words; int vregno; int sysv_gregno; scalar_t__ prototype; scalar_t__ stdarg; } ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 scalar_t__ ABI_AIX ; 
 int ABI_V4 ; 
 scalar_t__ ALTIVEC_VECTOR_MODE (int) ; 
 int BLKmode ; 
 int CALL_LIBCALL ; 
 int CALL_V4_CLEAR_FP_ARGS ; 
 int CALL_V4_SET_FP_ARGS ; 
 int DCmode ; 
 scalar_t__ DEFAULT_ABI ; 
 int DFmode ; 
 int DImode ; 
 unsigned long FP_ARG_MAX_REG ; 
 scalar_t__ FP_ARG_MIN_REG ; 
 scalar_t__ FP_ARG_V4_MAX_REG ; 
 scalar_t__ GEN_INT (int) ; 
 int GET_MODE_SIZE (int) ; 
 int GP_ARG_MAX_REG ; 
 int GP_ARG_MIN_REG ; 
 int GP_ARG_NUM_REG ; 
 scalar_t__ NULL_RTX ; 
 int Pmode ; 
 scalar_t__ RECORD_TYPE ; 
 int SFmode ; 
 int SImode ; 
 scalar_t__ SPE_VECTOR_MODE (int) ; 
 scalar_t__ TARGET_32BIT ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_ALTIVEC_ABI ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 int /*<<< orphan*/  TARGET_IEEEQUAD ; 
 scalar_t__ TARGET_NO_PROTOTYPE ; 
 scalar_t__ TARGET_POWERPC64 ; 
 scalar_t__ TARGET_SPE ; 
 scalar_t__ TARGET_SPE_ABI ; 
 scalar_t__ TARGET_XL_COMPAT ; 
 int TFmode ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ USE_ALTIVEC_FOR_ARG_P (TYPE_1__*,int,scalar_t__,int) ; 
 scalar_t__ USE_FP_FOR_ARG_P (TYPE_1__*,int,scalar_t__) ; 
 scalar_t__ VECTOR_TYPE ; 
 int VOIDmode ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtvec_v (int,scalar_t__*) ; 
 scalar_t__ gen_rtx_EXPR_LIST (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_PARALLEL (int,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_REG (int,int) ; 
 int int_size_in_bytes (scalar_t__) ; 
 void* rs6000_arg_size (int,scalar_t__) ; 
 scalar_t__ rs6000_darwin64_abi ; 
 scalar_t__ rs6000_darwin64_record_arg (TYPE_1__*,scalar_t__,int,int) ; 
 scalar_t__ rs6000_mixed_function_arg (int,scalar_t__,int) ; 
 int rs6000_parm_start (int,scalar_t__,int) ; 
 scalar_t__ rs6000_spe_function_arg (TYPE_1__*,int,scalar_t__) ; 

rtx
function_arg (CUMULATIVE_ARGS *cum, enum machine_mode mode,
	      tree type, int named)
{
  enum rs6000_abi abi = DEFAULT_ABI;

  /* Return a marker to indicate whether CR1 needs to set or clear the
     bit that V.4 uses to say fp args were passed in registers.
     Assume that we don't need the marker for software floating point,
     or compiler generated library calls.  */
  if (mode == VOIDmode)
    {
      if (abi == ABI_V4
	  && (cum->call_cookie & CALL_LIBCALL) == 0
	  && (cum->stdarg
	      || (cum->nargs_prototype < 0
		  && (cum->prototype || TARGET_NO_PROTOTYPE))))
	{
	  /* For the SPE, we need to crxor CR6 always.  */
	  if (TARGET_SPE_ABI)
	    return GEN_INT (cum->call_cookie | CALL_V4_SET_FP_ARGS);
	  else if (TARGET_HARD_FLOAT && TARGET_FPRS)
	    return GEN_INT (cum->call_cookie
			    | ((cum->fregno == FP_ARG_MIN_REG)
			       ? CALL_V4_SET_FP_ARGS
			       : CALL_V4_CLEAR_FP_ARGS));
	}

      return GEN_INT (cum->call_cookie);
    }

  if (rs6000_darwin64_abi && mode == BLKmode
      && TREE_CODE (type) == RECORD_TYPE)
    {
      rtx rslt = rs6000_darwin64_record_arg (cum, type, named, false);
      if (rslt != NULL_RTX)
	return rslt;
      /* Else fall through to usual handling.  */
    }

  if (USE_ALTIVEC_FOR_ARG_P (cum, mode, type, named))
    if (TARGET_64BIT && ! cum->prototype)
      {
	/* Vector parameters get passed in vector register
	   and also in GPRs or memory, in absence of prototype.  */
	int align_words;
	rtx slot;
	align_words = (cum->words + 1) & ~1;

	if (align_words >= GP_ARG_NUM_REG)
	  {
	    slot = NULL_RTX;
	  }
	else
	  {
	    slot = gen_rtx_REG (mode, GP_ARG_MIN_REG + align_words);
	  }
	return gen_rtx_PARALLEL (mode,
		 gen_rtvec (2,
			    gen_rtx_EXPR_LIST (VOIDmode,
					       slot, const0_rtx),
			    gen_rtx_EXPR_LIST (VOIDmode,
					       gen_rtx_REG (mode, cum->vregno),
					       const0_rtx)));
      }
    else
      return gen_rtx_REG (mode, cum->vregno);
  else if (TARGET_ALTIVEC_ABI
	   && (ALTIVEC_VECTOR_MODE (mode)
	       || (type && TREE_CODE (type) == VECTOR_TYPE
		   && int_size_in_bytes (type) == 16)))
    {
      if (named || abi == ABI_V4)
	return NULL_RTX;
      else
	{
	  /* Vector parameters to varargs functions under AIX or Darwin
	     get passed in memory and possibly also in GPRs.  */
	  int align, align_words, n_words;
	  enum machine_mode part_mode;

	  /* Vector parameters must be 16-byte aligned.  This places them at
	     2 mod 4 in terms of words in 32-bit mode, since the parameter
	     save area starts at offset 24 from the stack.  In 64-bit mode,
	     they just have to start on an even word, since the parameter
	     save area is 16-byte aligned.  */
	  if (TARGET_32BIT)
	    align = (2 - cum->words) & 3;
	  else
	    align = cum->words & 1;
	  align_words = cum->words + align;

	  /* Out of registers?  Memory, then.  */
	  if (align_words >= GP_ARG_NUM_REG)
	    return NULL_RTX;

	  if (TARGET_32BIT && TARGET_POWERPC64)
	    return rs6000_mixed_function_arg (mode, type, align_words);

	  /* The vector value goes in GPRs.  Only the part of the
	     value in GPRs is reported here.  */
	  part_mode = mode;
	  n_words = rs6000_arg_size (mode, type);
	  if (align_words + n_words > GP_ARG_NUM_REG)
	    /* Fortunately, there are only two possibilities, the value
	       is either wholly in GPRs or half in GPRs and half not.  */
	    part_mode = DImode;

	  return gen_rtx_REG (part_mode, GP_ARG_MIN_REG + align_words);
	}
    }
  else if (TARGET_SPE_ABI && TARGET_SPE
	   && (SPE_VECTOR_MODE (mode)
	       || (TARGET_E500_DOUBLE && (mode == DFmode
					  || mode == DCmode))))
    return rs6000_spe_function_arg (cum, mode, type);

  else if (abi == ABI_V4)
    {
      if (TARGET_HARD_FLOAT && TARGET_FPRS
	  && (mode == SFmode || mode == DFmode
	      || (mode == TFmode && !TARGET_IEEEQUAD)))
	{
	  if (cum->fregno + (mode == TFmode ? 1 : 0) <= FP_ARG_V4_MAX_REG)
	    return gen_rtx_REG (mode, cum->fregno);
	  else
	    return NULL_RTX;
	}
      else
	{
	  int n_words = rs6000_arg_size (mode, type);
	  int gregno = cum->sysv_gregno;

	  /* Long long and SPE vectors are put in (r3,r4), (r5,r6),
	     (r7,r8) or (r9,r10).  As does any other 2 word item such
	     as complex int due to a historical mistake.  */
	  if (n_words == 2)
	    gregno += (1 - gregno) & 1;

	  /* Multi-reg args are not split between registers and stack.  */
	  if (gregno + n_words - 1 > GP_ARG_MAX_REG)
	    return NULL_RTX;

	  if (TARGET_32BIT && TARGET_POWERPC64)
	    return rs6000_mixed_function_arg (mode, type,
					      gregno - GP_ARG_MIN_REG);
	  return gen_rtx_REG (mode, gregno);
	}
    }
  else
    {
      int align_words = rs6000_parm_start (mode, type, cum->words);

      if (USE_FP_FOR_ARG_P (cum, mode, type))
	{
	  rtx rvec[GP_ARG_NUM_REG + 1];
	  rtx r;
	  int k;
	  bool needs_psave;
	  enum machine_mode fmode = mode;
	  unsigned long n_fpreg = (GET_MODE_SIZE (mode) + 7) >> 3;

	  if (cum->fregno + n_fpreg > FP_ARG_MAX_REG + 1)
	    {
	      /* Currently, we only ever need one reg here because complex
		 doubles are split.  */
	      gcc_assert (cum->fregno == FP_ARG_MAX_REG && fmode == TFmode);

	      /* Long double split over regs and memory.  */
	      fmode = DFmode;
	    }

	  /* Do we also need to pass this arg in the parameter save
	     area?  */
	  needs_psave = (type
			 && (cum->nargs_prototype <= 0
			     || (DEFAULT_ABI == ABI_AIX
				 && TARGET_XL_COMPAT
				 && align_words >= GP_ARG_NUM_REG)));

	  if (!needs_psave && mode == fmode)
	    return gen_rtx_REG (fmode, cum->fregno);

	  k = 0;
	  if (needs_psave)
	    {
	      /* Describe the part that goes in gprs or the stack.
		 This piece must come first, before the fprs.  */
	      if (align_words < GP_ARG_NUM_REG)
		{
		  unsigned long n_words = rs6000_arg_size (mode, type);

		  if (align_words + n_words > GP_ARG_NUM_REG
		      || (TARGET_32BIT && TARGET_POWERPC64))
		    {
		      /* If this is partially on the stack, then we only
			 include the portion actually in registers here.  */
		      enum machine_mode rmode = TARGET_32BIT ? SImode : DImode;
		      rtx off;
		      int i = 0;
		      if (align_words + n_words > GP_ARG_NUM_REG)
			/* Not all of the arg fits in gprs.  Say that it
			   goes in memory too, using a magic NULL_RTX
			   component.  Also see comment in
			   rs6000_mixed_function_arg for why the normal
			   function_arg_partial_nregs scheme doesn't work
			   in this case. */
			rvec[k++] = gen_rtx_EXPR_LIST (VOIDmode, NULL_RTX,
						       const0_rtx);
		      do
			{
			  r = gen_rtx_REG (rmode,
					   GP_ARG_MIN_REG + align_words);
			  off = GEN_INT (i++ * GET_MODE_SIZE (rmode));
			  rvec[k++] = gen_rtx_EXPR_LIST (VOIDmode, r, off);
			}
		      while (++align_words < GP_ARG_NUM_REG && --n_words != 0);
		    }
		  else
		    {
		      /* The whole arg fits in gprs.  */
		      r = gen_rtx_REG (mode, GP_ARG_MIN_REG + align_words);
		      rvec[k++] = gen_rtx_EXPR_LIST (VOIDmode, r, const0_rtx);
		    }
		}
	      else
		/* It's entirely in memory.  */
		rvec[k++] = gen_rtx_EXPR_LIST (VOIDmode, NULL_RTX, const0_rtx);
	    }

	  /* Describe where this piece goes in the fprs.  */
	  r = gen_rtx_REG (fmode, cum->fregno);
	  rvec[k++] = gen_rtx_EXPR_LIST (VOIDmode, r, const0_rtx);

	  return gen_rtx_PARALLEL (mode, gen_rtvec_v (k, rvec));
	}
      else if (align_words < GP_ARG_NUM_REG)
	{
	  if (TARGET_32BIT && TARGET_POWERPC64)
	    return rs6000_mixed_function_arg (mode, type, align_words);

	  if (mode == BLKmode)
	    mode = Pmode;

	  return gen_rtx_REG (mode, GP_ARG_MIN_REG + align_words);
	}
      else
	return NULL_RTX;
    }
}