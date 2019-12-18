#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum attr_type { ____Placeholder_attr_type } attr_type ;
struct TYPE_2__ {int n_operands; int /*<<< orphan*/ * operand; } ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_PENTIUM ; 
 int TYPE_LEA ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_insn_cached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int modified_in_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ recog_data ; 

__attribute__((used)) static int
ix86_agi_dependent (rtx insn, rtx dep_insn, enum attr_type insn_type)
{
  rtx addr;

  if (insn_type == TYPE_LEA
      && TARGET_PENTIUM)
    {
      addr = PATTERN (insn);

      if (GET_CODE (addr) == PARALLEL)
	addr = XVECEXP (addr, 0, 0);

      gcc_assert (GET_CODE (addr) == SET);

      addr = SET_SRC (addr);
    }
  else
    {
      int i;
      extract_insn_cached (insn);
      for (i = recog_data.n_operands - 1; i >= 0; --i)
	if (GET_CODE (recog_data.operand[i]) == MEM)
	  {
	    addr = XEXP (recog_data.operand[i], 0);
	    goto found;
	  }
      return 0;
    found:;
    }

  return modified_in_p (addr, dep_insn);
}