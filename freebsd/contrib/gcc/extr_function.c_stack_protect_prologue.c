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
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ rtx ;
struct TYPE_4__ {int /*<<< orphan*/  stack_protect_guard; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stack_protect_guard ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 scalar_t__ HAVE_stack_protect_set ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_stack_protect_set (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__ targetm ; 
 scalar_t__ validize_mem (int /*<<< orphan*/ ) ; 

void
stack_protect_prologue (void)
{
  tree guard_decl = targetm.stack_protect_guard ();
  rtx x, y;

  /* Avoid expand_expr here, because we don't want guard_decl pulled
     into registers unless absolutely necessary.  And we know that
     cfun->stack_protect_guard is a local stack slot, so this skips
     all the fluff.  */
  x = validize_mem (DECL_RTL (cfun->stack_protect_guard));
  y = validize_mem (DECL_RTL (guard_decl));

  /* Allow the target to copy from Y to X without leaking Y into a
     register.  */
  if (HAVE_stack_protect_set)
    {
      rtx insn = gen_stack_protect_set (x, y);
      if (insn)
	{
	  emit_insn (insn);
	  return;
	}
    }

  /* Otherwise do a straight move.  */
  emit_move_insn (x, y);
}