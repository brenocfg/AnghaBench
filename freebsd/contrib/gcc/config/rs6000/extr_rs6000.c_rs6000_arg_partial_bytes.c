#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_5__ {scalar_t__ nargs_prototype; scalar_t__ fregno; int /*<<< orphan*/  words; } ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 scalar_t__ ABI_AIX ; 
 scalar_t__ ABI_V4 ; 
 int BLKmode ; 
 scalar_t__ DEFAULT_ABI ; 
 scalar_t__ FP_ARG_MAX_REG ; 
 int GET_MODE_SIZE (int) ; 
 int GP_ARG_NUM_REG ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TARGET_32BIT ; 
 scalar_t__ TARGET_DEBUG_ARG ; 
 scalar_t__ TARGET_XL_COMPAT ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ USE_ALTIVEC_FOR_ARG_P (TYPE_1__*,int,scalar_t__,int) ; 
 scalar_t__ USE_FP_FOR_ARG_P (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ int_size_in_bytes (scalar_t__) ; 
 int rs6000_arg_size (int,scalar_t__) ; 
 scalar_t__ rs6000_darwin64_abi ; 
 int rs6000_parm_start (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
rs6000_arg_partial_bytes (CUMULATIVE_ARGS *cum, enum machine_mode mode,
			  tree type, bool named)
{
  int ret = 0;
  int align_words;

  if (DEFAULT_ABI == ABI_V4)
    return 0;

  if (USE_ALTIVEC_FOR_ARG_P (cum, mode, type, named)
      && cum->nargs_prototype >= 0)
    return 0;

  /* In this complicated case we just disable the partial_nregs code.  */
  if (rs6000_darwin64_abi && mode == BLKmode
      && TREE_CODE (type) == RECORD_TYPE
      && int_size_in_bytes (type) > 0)
    return 0;

  align_words = rs6000_parm_start (mode, type, cum->words);

  if (USE_FP_FOR_ARG_P (cum, mode, type))
    {
      /* If we are passing this arg in the fixed parameter save area
	 (gprs or memory) as well as fprs, then this function should
	 return the number of partial bytes passed in the parameter
	 save area rather than partial bytes passed in fprs.  */
      if (type
	  && (cum->nargs_prototype <= 0
	      || (DEFAULT_ABI == ABI_AIX
		  && TARGET_XL_COMPAT
		  && align_words >= GP_ARG_NUM_REG)))
	return 0;
      else if (cum->fregno + ((GET_MODE_SIZE (mode) + 7) >> 3)
	       > FP_ARG_MAX_REG + 1)
	ret = (FP_ARG_MAX_REG + 1 - cum->fregno) * 8;
      else if (cum->nargs_prototype >= 0)
	return 0;
    }

  if (align_words < GP_ARG_NUM_REG
      && GP_ARG_NUM_REG < align_words + rs6000_arg_size (mode, type))
    ret = (GP_ARG_NUM_REG - align_words) * (TARGET_32BIT ? 4 : 8);

  if (ret != 0 && TARGET_DEBUG_ARG)
    fprintf (stderr, "rs6000_arg_partial_bytes: %d\n", ret);

  return ret;
}