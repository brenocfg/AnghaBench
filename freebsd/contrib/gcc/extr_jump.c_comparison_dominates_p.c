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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  EQ 139 
#define  GE 138 
 int GEU ; 
#define  GT 137 
#define  GTU 136 
#define  LE 135 
 int LEU ; 
#define  LT 134 
#define  LTGT 133 
#define  LTU 132 
 int NE ; 
 int ORDERED ; 
#define  UNEQ 131 
 int UNGE ; 
#define  UNGT 130 
 int UNKNOWN ; 
 int UNLE ; 
#define  UNLT 129 
#define  UNORDERED 128 

int
comparison_dominates_p (enum rtx_code code1, enum rtx_code code2)
{
  /* UNKNOWN comparison codes can happen as a result of trying to revert
     comparison codes.
     They can't match anything, so we have to reject them here.  */
  if (code1 == UNKNOWN || code2 == UNKNOWN)
    return 0;

  if (code1 == code2)
    return 1;

  switch (code1)
    {
    case UNEQ:
      if (code2 == UNLE || code2 == UNGE)
	return 1;
      break;

    case EQ:
      if (code2 == LE || code2 == LEU || code2 == GE || code2 == GEU
	  || code2 == ORDERED)
	return 1;
      break;

    case UNLT:
      if (code2 == UNLE || code2 == NE)
	return 1;
      break;

    case LT:
      if (code2 == LE || code2 == NE || code2 == ORDERED || code2 == LTGT)
	return 1;
      break;

    case UNGT:
      if (code2 == UNGE || code2 == NE)
	return 1;
      break;

    case GT:
      if (code2 == GE || code2 == NE || code2 == ORDERED || code2 == LTGT)
	return 1;
      break;

    case GE:
    case LE:
      if (code2 == ORDERED)
	return 1;
      break;

    case LTGT:
      if (code2 == NE || code2 == ORDERED)
	return 1;
      break;

    case LTU:
      if (code2 == LEU || code2 == NE)
	return 1;
      break;

    case GTU:
      if (code2 == GEU || code2 == NE)
	return 1;
      break;

    case UNORDERED:
      if (code2 == NE || code2 == UNEQ || code2 == UNLE || code2 == UNLT
	  || code2 == UNGE || code2 == UNGT)
	return 1;
      break;

    default:
      break;
    }

  return 0;
}