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
 int INSN_SHUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JUMP_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int uid_shuid ; 

int
final_forward_branch_p (rtx insn)
{
  int insn_id, label_id;

  gcc_assert (uid_shuid);
  insn_id = INSN_SHUID (insn);
  label_id = INSN_SHUID (JUMP_LABEL (insn));
  /* We've hit some insns that does not have id information available.  */
  gcc_assert (insn_id && label_id);
  return insn_id < label_id;
}