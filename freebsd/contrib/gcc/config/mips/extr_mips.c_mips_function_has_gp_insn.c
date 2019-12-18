#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {int has_gp_insn_p; } ;

/* Variables and functions */
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GOT_UNSET ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ USE ; 
 int /*<<< orphan*/  VOIDmode ; 
 TYPE_2__* cfun ; 
 scalar_t__ get_attr_got (scalar_t__) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  pop_topmost_sequence () ; 
 int /*<<< orphan*/  push_topmost_sequence () ; 
 scalar_t__ small_data_pattern (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mips_function_has_gp_insn (void)
{
  /* Don't bother rechecking if we found one last time.  */
  if (!cfun->machine->has_gp_insn_p)
    {
      rtx insn;

      push_topmost_sequence ();
      for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
	if (INSN_P (insn)
	    && GET_CODE (PATTERN (insn)) != USE
	    && GET_CODE (PATTERN (insn)) != CLOBBER
	    && (get_attr_got (insn) != GOT_UNSET
		|| small_data_pattern (PATTERN (insn), VOIDmode)))
	  break;
      pop_topmost_sequence ();

      cfun->machine->has_gp_insn_p = (insn != 0);
    }
  return cfun->machine->has_gp_insn_p;
}