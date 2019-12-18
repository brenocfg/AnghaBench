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
struct TYPE_3__ {scalar_t__ (* expand_builtin_saveregs ) () ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  emit_insn_after (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  entry_of_function () ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  pop_topmost_sequence () ; 
 int /*<<< orphan*/  push_topmost_sequence () ; 
 scalar_t__ saveregs_value ; 
 int /*<<< orphan*/  start_sequence () ; 
 scalar_t__ stub1 () ; 
 TYPE_2__ targetm ; 

rtx
expand_builtin_saveregs (void)
{
  rtx val, seq;

  /* Don't do __builtin_saveregs more than once in a function.
     Save the result of the first call and reuse it.  */
  if (saveregs_value != 0)
    return saveregs_value;

  /* When this function is called, it means that registers must be
     saved on entry to this function.  So we migrate the call to the
     first insn of this function.  */

  start_sequence ();

  /* Do whatever the machine needs done in this case.  */
  val = targetm.calls.expand_builtin_saveregs ();

  seq = get_insns ();
  end_sequence ();

  saveregs_value = val;

  /* Put the insns after the NOTE that starts the function.  If this
     is inside a start_sequence, make the outer-level insn chain current, so
     the code is placed at the start of the function.  */
  push_topmost_sequence ();
  emit_insn_after (seq, entry_of_function ());
  pop_topmost_sequence ();

  return val;
}