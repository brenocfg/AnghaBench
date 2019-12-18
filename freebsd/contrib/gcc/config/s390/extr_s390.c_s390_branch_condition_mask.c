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
typedef  scalar_t__ rtx ;

/* Variables and functions */
#define  CCANmode 160 
#define  CCAPmode 159 
#define  CCL1mode 158 
#define  CCL2mode 157 
#define  CCL3mode 156 
#define  CCLmode 155 
#define  CCSRmode 154 
#define  CCSmode 153 
#define  CCT1mode 152 
#define  CCT2mode 151 
#define  CCT3mode 150 
#define  CCURmode 149 
#define  CCUmode 148 
#define  CCZ1mode 147 
#define  CCZmode 146 
 scalar_t__ CC_REGNUM ; 
#define  EQ 145 
#define  GE 144 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
#define  GEU 143 
#define  GT 142 
#define  GTU 141 
#define  LE 140 
#define  LEU 139 
#define  LT 138 
#define  LTGT 137 
#define  LTU 136 
#define  NE 135 
#define  ORDERED 134 
 scalar_t__ REG ; 
 scalar_t__ REGNO (scalar_t__) ; 
#define  UNEQ 133 
#define  UNGE 132 
#define  UNGT 131 
#define  UNLE 130 
#define  UNLT 129 
#define  UNORDERED 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

int
s390_branch_condition_mask (rtx code)
{
  const int CC0 = 1 << 3;
  const int CC1 = 1 << 2;
  const int CC2 = 1 << 1;
  const int CC3 = 1 << 0;

  gcc_assert (GET_CODE (XEXP (code, 0)) == REG);
  gcc_assert (REGNO (XEXP (code, 0)) == CC_REGNUM);
  gcc_assert (XEXP (code, 1) == const0_rtx);

  switch (GET_MODE (XEXP (code, 0)))
    {
    case CCZmode:
    case CCZ1mode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC0;
	case NE:	return CC1 | CC2 | CC3;
	default:	return -1;
        }
      break;

    case CCT1mode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC1;
	case NE:	return CC0 | CC2 | CC3;
	default:	return -1;
        }
      break;

    case CCT2mode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC2;
	case NE:	return CC0 | CC1 | CC3;
	default:	return -1;
        }
      break;

    case CCT3mode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC3;
	case NE:	return CC0 | CC1 | CC2;
	default:	return -1;
        }
      break;

    case CCLmode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC0 | CC2;
	case NE:	return CC1 | CC3;
	default:	return -1;
        }
      break;

    case CCL1mode:
      switch (GET_CODE (code))
        {
	case LTU:	return CC2 | CC3;  /* carry */
	case GEU:	return CC0 | CC1;  /* no carry */
	default:	return -1;
        }
      break;

    case CCL2mode:
      switch (GET_CODE (code))
        {
	case GTU:	return CC0 | CC1;  /* borrow */
	case LEU:	return CC2 | CC3;  /* no borrow */
	default:	return -1;
        }
      break;

    case CCL3mode:
      switch (GET_CODE (code))
	{
	case EQ:	return CC0 | CC2;
	case NE:	return CC1 | CC3;
	case LTU:	return CC1;
	case GTU:	return CC3;
	case LEU:	return CC1 | CC2;
	case GEU:	return CC2 | CC3;
	default:	return -1;
	}

    case CCUmode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC0;
        case NE:	return CC1 | CC2 | CC3;
        case LTU:	return CC1;
        case GTU:	return CC2;
        case LEU:	return CC0 | CC1;
        case GEU:	return CC0 | CC2;
	default:	return -1;
        }
      break;

    case CCURmode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC0;
        case NE:	return CC2 | CC1 | CC3;
        case LTU:	return CC2;
        case GTU:	return CC1;
        case LEU:	return CC0 | CC2;
        case GEU:	return CC0 | CC1;
	default:	return -1;
        }
      break;

    case CCAPmode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC0;
        case NE:	return CC1 | CC2 | CC3;
        case LT:	return CC1 | CC3;
        case GT:	return CC2;
        case LE:	return CC0 | CC1 | CC3;
        case GE:	return CC0 | CC2;
	default:	return -1;
        }
      break;

    case CCANmode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC0;
        case NE:	return CC1 | CC2 | CC3;
        case LT:	return CC1;
        case GT:	return CC2 | CC3;
        case LE:	return CC0 | CC1;
        case GE:	return CC0 | CC2 | CC3;
	default:	return -1;
        }
      break;

    case CCSmode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC0;
        case NE:	return CC1 | CC2 | CC3;
        case LT:	return CC1;
        case GT:	return CC2;
        case LE:	return CC0 | CC1;
        case GE:	return CC0 | CC2;
	case UNORDERED:	return CC3;
	case ORDERED:	return CC0 | CC1 | CC2;
	case UNEQ:	return CC0 | CC3;
        case UNLT:	return CC1 | CC3;
        case UNGT:	return CC2 | CC3;
        case UNLE:	return CC0 | CC1 | CC3;
        case UNGE:	return CC0 | CC2 | CC3;
	case LTGT:	return CC1 | CC2;
	default:	return -1;
        }
      break;

    case CCSRmode:
      switch (GET_CODE (code))
        {
        case EQ:	return CC0;
        case NE:	return CC2 | CC1 | CC3;
        case LT:	return CC2;
        case GT:	return CC1;
        case LE:	return CC0 | CC2;
        case GE:	return CC0 | CC1;
	case UNORDERED:	return CC3;
	case ORDERED:	return CC0 | CC2 | CC1;
	case UNEQ:	return CC0 | CC3;
        case UNLT:	return CC2 | CC3;
        case UNGT:	return CC1 | CC3;
        case UNLE:	return CC0 | CC2 | CC3;
        case UNGE:	return CC0 | CC1 | CC3;
	case LTGT:	return CC2 | CC1;
	default:	return -1;
        }
      break;

    default:
      return -1;
    }
}