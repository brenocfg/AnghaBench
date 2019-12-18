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
struct reg_flags {int is_fp; int is_and; int is_or; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int AND ; 
#define  CALL 129 
 int /*<<< orphan*/  COMPARISON_P (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
#define  IF_THEN_ELSE 128 
 int IOR ; 
 int /*<<< orphan*/  SCALAR_FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_set_flags (rtx x, struct reg_flags *pflags)
{
  rtx src = SET_SRC (x);

  switch (GET_CODE (src))
    {
    case CALL:
      return;

    case IF_THEN_ELSE:
      /* There are four cases here:
	 (1) The destination is (pc), in which case this is a branch,
	 nothing here applies.
	 (2) The destination is ar.lc, in which case this is a
	 doloop_end_internal,
	 (3) The destination is an fp register, in which case this is
	 an fselect instruction.
	 (4) The condition has (unspec [(reg)] UNSPEC_LDC), in which case 
	 this is a check load.
	 In all cases, nothing we do in this function applies.  */
      return;

    default:
      if (COMPARISON_P (src)
	  && SCALAR_FLOAT_MODE_P (GET_MODE (XEXP (src, 0))))
	/* Set pflags->is_fp to 1 so that we know we're dealing
	   with a floating point comparison when processing the
	   destination of the SET.  */
	pflags->is_fp = 1;

      /* Discover if this is a parallel comparison.  We only handle
	 and.orcm and or.andcm at present, since we must retain a
	 strict inverse on the predicate pair.  */
      else if (GET_CODE (src) == AND)
	pflags->is_and = 1;
      else if (GET_CODE (src) == IOR)
	pflags->is_or = 1;

      break;
    }
}