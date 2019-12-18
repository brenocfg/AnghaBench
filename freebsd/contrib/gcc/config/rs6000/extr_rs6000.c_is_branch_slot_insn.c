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
typedef  enum attr_type { ____Placeholder_attr_type } attr_type ;

/* Variables and functions */
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int TYPE_BRANCH ; 
 int TYPE_JMPREG ; 
 scalar_t__ USE ; 
 int get_attr_type (int /*<<< orphan*/ ) ; 
 scalar_t__ rs6000_sched_groups ; 

__attribute__((used)) static bool
is_branch_slot_insn (rtx insn)
{
  if (!insn || !INSN_P (insn)
      || GET_CODE (PATTERN (insn)) == USE
      || GET_CODE (PATTERN (insn)) == CLOBBER)
    return false;

  if (rs6000_sched_groups)
    {
      enum attr_type type = get_attr_type (insn);
      if (type == TYPE_BRANCH || type == TYPE_JMPREG)
	return true;
      return false;
    }

  return false;
}