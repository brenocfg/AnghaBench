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

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ addr_generation_dependency_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
s390_agen_dep_p (rtx dep_insn, rtx insn)
{
  rtx dep_rtx = PATTERN (dep_insn);
  int i;

  if (GET_CODE (dep_rtx) == SET
      && addr_generation_dependency_p (dep_rtx, insn))
    return 1;
  else if (GET_CODE (dep_rtx) == PARALLEL)
    {
      for (i = 0; i < XVECLEN (dep_rtx, 0); i++)
	{
	  if (addr_generation_dependency_p (XVECEXP (dep_rtx, 0, i), insn))
	    return 1;
	}
    }
  return 0;
}