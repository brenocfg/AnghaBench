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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_TO_TARGET_SINGLE (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  SPARC_SETHI_P (long) ; 
 int /*<<< orphan*/  SPARC_SIMM13_P (long) ; 

int
fp_high_losum_p (rtx op)
{
  /* The constraints calling this should only be in
     SFmode move insns, so any constant which cannot
     be moved using a single insn will do.  */
  if (GET_CODE (op) == CONST_DOUBLE)
    {
      REAL_VALUE_TYPE r;
      long i;

      REAL_VALUE_FROM_CONST_DOUBLE (r, op);
      REAL_VALUE_TO_TARGET_SINGLE (r, i);
      return !SPARC_SIMM13_P (i) && !SPARC_SETHI_P (i);
    }

  return 0;
}