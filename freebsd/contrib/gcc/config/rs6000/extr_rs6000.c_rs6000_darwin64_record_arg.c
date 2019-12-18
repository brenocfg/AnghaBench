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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_5__ {int words; int named; scalar_t__ use_stack; scalar_t__ intoffset; } ;
typedef  int HOST_WIDE_INT ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int BITS_PER_WORD ; 
 int /*<<< orphan*/  BLKmode ; 
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gen_rtvec_v (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int int_size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs6000_darwin64_record_arg_flush (TYPE_1__*,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rs6000_darwin64_record_arg_recurse (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static rtx
rs6000_darwin64_record_arg (CUMULATIVE_ARGS *orig_cum, tree type,
			    int named, bool retval)
{
  rtx rvec[FIRST_PSEUDO_REGISTER];
  int k = 1, kbase = 1;
  HOST_WIDE_INT typesize = int_size_in_bytes (type);
  /* This is a copy; modifications are not visible to our caller.  */
  CUMULATIVE_ARGS copy_cum = *orig_cum;
  CUMULATIVE_ARGS *cum = &copy_cum;

  /* Pad to 16 byte boundary if needed.  */
  if (!retval && TYPE_ALIGN (type) >= 2 * BITS_PER_WORD
      && (cum->words % 2) != 0)
    cum->words++;

  cum->intoffset = 0;
  cum->use_stack = 0;
  cum->named = named;

  /* Put entries into rvec[] for individual FP and vector fields, and
     for the chunks of memory that go in int regs.  Note we start at
     element 1; 0 is reserved for an indication of using memory, and
     may or may not be filled in below. */
  rs6000_darwin64_record_arg_recurse (cum, type, 0, rvec, &k);
  rs6000_darwin64_record_arg_flush (cum, typesize * BITS_PER_UNIT, rvec, &k);

  /* If any part of the struct went on the stack put all of it there.
     This hack is because the generic code for
     FUNCTION_ARG_PARTIAL_NREGS cannot handle cases where the register
     parts of the struct are not at the beginning.  */
  if (cum->use_stack)
    {
      if (retval)
	return NULL_RTX;    /* doesn't go in registers at all */
      kbase = 0;
      rvec[0] = gen_rtx_EXPR_LIST (VOIDmode, NULL_RTX, const0_rtx);
    }
  if (k > 1 || cum->use_stack)
    return gen_rtx_PARALLEL (BLKmode, gen_rtvec_v (k - kbase, &rvec[kbase]));
  else
    return NULL_RTX;
}