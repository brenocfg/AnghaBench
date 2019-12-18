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
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {int /*<<< orphan*/  n_mos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  INT_MEM_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 TYPE_1__* VTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ offset_valid_for_tracked_p (int /*<<< orphan*/ ) ; 
 scalar_t__ track_expr_p (scalar_t__) ; 

__attribute__((used)) static int
count_uses (rtx *loc, void *insn)
{
  basic_block bb = BLOCK_FOR_INSN ((rtx) insn);

  if (REG_P (*loc))
    {
      gcc_assert (REGNO (*loc) < FIRST_PSEUDO_REGISTER);
      VTI (bb)->n_mos++;
    }
  else if (MEM_P (*loc)
	   && MEM_EXPR (*loc)
	   && track_expr_p (MEM_EXPR (*loc))
	   && offset_valid_for_tracked_p (INT_MEM_OFFSET (*loc)))
    {
      VTI (bb)->n_mos++;
    }

  return 0;
}