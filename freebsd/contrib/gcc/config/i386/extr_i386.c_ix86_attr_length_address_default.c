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
struct TYPE_2__ {int n_operands; int /*<<< orphan*/ * operand; } ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_LEA ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_insn_cached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_attr_type (int /*<<< orphan*/ ) ; 
 int memory_address_length (int /*<<< orphan*/ ) ; 
 TYPE_1__ recog_data ; 

int
ix86_attr_length_address_default (rtx insn)
{
  int i;

  if (get_attr_type (insn) == TYPE_LEA)
    {
      rtx set = PATTERN (insn);

      if (GET_CODE (set) == PARALLEL)
	set = XVECEXP (set, 0, 0);

      gcc_assert (GET_CODE (set) == SET);

      return memory_address_length (SET_SRC (set));
    }

  extract_insn_cached (insn);
  for (i = recog_data.n_operands - 1; i >= 0; --i)
    if (GET_CODE (recog_data.operand[i]) == MEM)
      {
	return memory_address_length (XEXP (recog_data.operand[i], 0));
	break;
      }
  return 0;
}