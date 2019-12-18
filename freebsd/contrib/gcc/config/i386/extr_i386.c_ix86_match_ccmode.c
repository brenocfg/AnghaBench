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
#define  CCGCmode 132 
#define  CCGOCmode 131 
#define  CCNOmode 130 
#define  CCZmode 129 
#define  CCmode 128 
 scalar_t__ COMPARE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

int
ix86_match_ccmode (rtx insn, enum machine_mode req_mode)
{
  rtx set;
  enum machine_mode set_mode;

  set = PATTERN (insn);
  if (GET_CODE (set) == PARALLEL)
    set = XVECEXP (set, 0, 0);
  gcc_assert (GET_CODE (set) == SET);
  gcc_assert (GET_CODE (SET_SRC (set)) == COMPARE);

  set_mode = GET_MODE (SET_DEST (set));
  switch (set_mode)
    {
    case CCNOmode:
      if (req_mode != CCNOmode
	  && (req_mode != CCmode
	      || XEXP (SET_SRC (set), 1) != const0_rtx))
	return 0;
      break;
    case CCmode:
      if (req_mode == CCGCmode)
	return 0;
      /* FALLTHRU */
    case CCGCmode:
      if (req_mode == CCGOCmode || req_mode == CCNOmode)
	return 0;
      /* FALLTHRU */
    case CCGOCmode:
      if (req_mode == CCZmode)
	return 0;
      /* FALLTHRU */
    case CCZmode:
      break;

    default:
      gcc_unreachable ();
    }

  return (GET_MODE (SET_SRC (set)) == set_mode);
}