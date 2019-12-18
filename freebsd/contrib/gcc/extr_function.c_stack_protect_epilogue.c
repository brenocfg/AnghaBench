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
struct TYPE_3__ {int /*<<< orphan*/  (* stack_protect_fail ) () ;int /*<<< orphan*/  (* stack_protect_guard ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EQ ; 
 scalar_t__ HAVE_stack_protect_test ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PRED_NORETURN ; 
 int /*<<< orphan*/  TAKEN ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  expand_expr_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_label_rtx () ; 
 scalar_t__ gen_stack_protect_test (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ get_last_insn () ; 
 int /*<<< orphan*/  predict_insn_def (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_mode ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 TYPE_1__ targetm ; 
 scalar_t__ validize_mem (int /*<<< orphan*/ ) ; 

void
stack_protect_epilogue (void)
{
  tree guard_decl = targetm.stack_protect_guard ();
  rtx label = gen_label_rtx ();
  rtx x, y, tmp;

  /* Avoid expand_expr here, because we don't want guard_decl pulled
     into registers unless absolutely necessary.  And we know that
     cfun->stack_protect_guard is a local stack slot, so this skips
     all the fluff.  */
  x = validize_mem (DECL_RTL (cfun->stack_protect_guard));
  y = validize_mem (DECL_RTL (guard_decl));

  /* Allow the target to compare Y with X without leaking either into
     a register.  */
  if (HAVE_stack_protect_test != 0)
    {
      tmp = gen_stack_protect_test (x, y, label);
      if (tmp)
	{
	  emit_insn (tmp);
	  goto done;
	}
    }

  emit_cmp_and_jump_insns (x, y, EQ, NULL_RTX, ptr_mode, 1, label);
 done:

  /* The noreturn predictor has been moved to the tree level.  The rtl-level
     predictors estimate this branch about 20%, which isn't enough to get
     things moved out of line.  Since this is the only extant case of adding
     a noreturn function at the rtl level, it doesn't seem worth doing ought
     except adding the prediction by hand.  */
  tmp = get_last_insn ();
  if (JUMP_P (tmp))
    predict_insn_def (tmp, PRED_NORETURN, TAKEN);

  expand_expr_stmt (targetm.stack_protect_fail ());
  emit_label (label);
}