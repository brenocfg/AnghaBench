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
struct s390_address {int /*<<< orphan*/  disp; int /*<<< orphan*/  indx; scalar_t__ literal_pool; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_LONG_DISPLACEMENT ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsettable_memref_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsettable_nonstrict_memref_p (int /*<<< orphan*/ ) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 scalar_t__ s390_decompose_address (int /*<<< orphan*/ ,struct s390_address*) ; 
 int /*<<< orphan*/  s390_decompose_shift_count (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s390_short_displacement (int /*<<< orphan*/ ) ; 

int
s390_mem_constraint (const char *str, rtx op)
{
  struct s390_address addr;
  char c = str[0];

  /* Check for offsettable variants of memory constraints.  */
  if (c == 'A')
    {
      /* Only accept non-volatile MEMs.  */
      if (!MEM_P (op) || MEM_VOLATILE_P (op))
	return 0;

      if ((reload_completed || reload_in_progress)
	  ? !offsettable_memref_p (op) : !offsettable_nonstrict_memref_p (op))
	return 0;

      c = str[1];
    }

  /* Check for non-literal-pool variants of memory constraints.  */
  else if (c == 'B')
    {
      if (GET_CODE (op) != MEM)
	return 0;
      if (!s390_decompose_address (XEXP (op, 0), &addr))
	return 0;
      if (addr.literal_pool)
	return 0;

      c = str[1];
    }

  switch (c)
    {
    case 'Q':
      if (GET_CODE (op) != MEM)
	return 0;
      if (!s390_decompose_address (XEXP (op, 0), &addr))
	return 0;
      if (addr.indx)
	return 0;

      if (TARGET_LONG_DISPLACEMENT)
	{
	  if (!s390_short_displacement (addr.disp))
	    return 0;
	}
      break;

    case 'R':
      if (GET_CODE (op) != MEM)
	return 0;

      if (TARGET_LONG_DISPLACEMENT)
	{
	  if (!s390_decompose_address (XEXP (op, 0), &addr))
	    return 0;
	  if (!s390_short_displacement (addr.disp))
	    return 0;
	}
      break;

    case 'S':
      if (!TARGET_LONG_DISPLACEMENT)
	return 0;
      if (GET_CODE (op) != MEM)
	return 0;
      if (!s390_decompose_address (XEXP (op, 0), &addr))
	return 0;
      if (addr.indx)
	return 0;
      if (s390_short_displacement (addr.disp))
	return 0;
      break;

    case 'T':
      if (!TARGET_LONG_DISPLACEMENT)
	return 0;
      if (GET_CODE (op) != MEM)
	return 0;
      /* Any invalid address here will be fixed up by reload,
	 so accept it for the most generic constraint.  */
      if (s390_decompose_address (XEXP (op, 0), &addr)
	  && s390_short_displacement (addr.disp))
	return 0;
      break;

    case 'U':
      if (TARGET_LONG_DISPLACEMENT)
	{
	  if (!s390_decompose_address (op, &addr))
	    return 0;
	  if (!s390_short_displacement (addr.disp))
	    return 0;
	}
      break;

    case 'W':
      if (!TARGET_LONG_DISPLACEMENT)
	return 0;
      /* Any invalid address here will be fixed up by reload,
	 so accept it for the most generic constraint.  */
      if (s390_decompose_address (op, &addr)
	  && s390_short_displacement (addr.disp))
	return 0;
      break;

    case 'Y':
      /* Simply check for the basic form of a shift count.  Reload will
	 take care of making sure we have a proper base register.  */
      if (!s390_decompose_shift_count (op, NULL, NULL))
	return 0;
      break;

    default:
      return 0;
    }

  return 1;
}