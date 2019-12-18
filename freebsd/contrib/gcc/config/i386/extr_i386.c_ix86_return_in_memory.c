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
typedef  int /*<<< orphan*/  tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 int BLKmode ; 
 scalar_t__ MS_AGGREGATE_RETURN ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_MMX ; 
 scalar_t__ TARGET_SSE ; 
 int TDmode ; 
 int TImode ; 
 scalar_t__ VECTOR_MODE_P (int) ; 
 int XFmode ; 
 int /*<<< orphan*/  examine_argument (int,int /*<<< orphan*/ ,int,int*,int*) ; 
 int int_size_in_bytes (int /*<<< orphan*/ ) ; 
 int type_natural_mode (int /*<<< orphan*/ ) ; 

int
ix86_return_in_memory (tree type)
{
  int needed_intregs, needed_sseregs, size;
  enum machine_mode mode = type_natural_mode (type);

  if (TARGET_64BIT)
    return !examine_argument (mode, type, 1, &needed_intregs, &needed_sseregs);

  if (mode == BLKmode)
    return 1;

  size = int_size_in_bytes (type);

  if (MS_AGGREGATE_RETURN && AGGREGATE_TYPE_P (type) && size <= 8)
    return 0;

  if (VECTOR_MODE_P (mode) || mode == TImode)
    {
      /* User-created vectors small enough to fit in EAX.  */
      if (size < 8)
	return 0;

      /* MMX/3dNow values are returned in MM0,
	 except when it doesn't exits.  */
      if (size == 8)
	return (TARGET_MMX ? 0 : 1);

      /* SSE values are returned in XMM0, except when it doesn't exist.  */
      if (size == 16)
	return (TARGET_SSE ? 0 : 1);
    }

  if (mode == XFmode)
    return 0;

  if (mode == TDmode)
    return 1;

  if (size > 12)
    return 1;
  return 0;
}