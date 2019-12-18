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
#define  CCANmode 141 
#define  CCAPmode 140 
 int CCAmode ; 
#define  CCL1mode 139 
#define  CCL2mode 138 
#define  CCL3mode 137 
#define  CCLmode 136 
#define  CCSRmode 135 
#define  CCSmode 134 
#define  CCT1mode 133 
#define  CCT2mode 132 
#define  CCT3mode 131 
 int CCTmode ; 
#define  CCURmode 130 
#define  CCUmode 129 
#define  CCZmode 128 
 int /*<<< orphan*/  CC_REGNO_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ REG ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static bool
s390_match_ccmode_set (rtx set, enum machine_mode req_mode)
{
  enum machine_mode set_mode;

  gcc_assert (GET_CODE (set) == SET);

  if (GET_CODE (SET_DEST (set)) != REG || !CC_REGNO_P (REGNO (SET_DEST (set))))
    return 1;

  set_mode = GET_MODE (SET_DEST (set));
  switch (set_mode)
    {
    case CCSmode:
    case CCSRmode:
    case CCUmode:
    case CCURmode:
    case CCLmode:
    case CCL1mode:
    case CCL2mode:
    case CCL3mode:
    case CCT1mode:
    case CCT2mode:
    case CCT3mode:
      if (req_mode != set_mode)
        return 0;
      break;

    case CCZmode:
      if (req_mode != CCSmode && req_mode != CCUmode && req_mode != CCTmode
	  && req_mode != CCSRmode && req_mode != CCURmode)
        return 0;
      break;

    case CCAPmode:
    case CCANmode:
      if (req_mode != CCAmode)
        return 0;
      break;

    default:
      gcc_unreachable ();
    }

  return (GET_MODE (SET_SRC (set)) == set_mode);
}