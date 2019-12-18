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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int /*<<< orphan*/  ehr_handler; int /*<<< orphan*/  ehr_stackadj; int /*<<< orphan*/  ehr_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  EH_RETURN_HANDLER_RTX ; 
 int /*<<< orphan*/  EH_RETURN_STACKADJ_RTX ; 
 scalar_t__ HAVE_eh_return ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  clobber_return_register () ; 
 int /*<<< orphan*/  const0_rtx ; 
 int current_function_calls_eh_return ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gen_eh_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 

void
expand_eh_return (void)
{
  rtx around_label;

  if (! cfun->eh->ehr_label)
    return;

  current_function_calls_eh_return = 1;

#ifdef EH_RETURN_STACKADJ_RTX
  emit_move_insn (EH_RETURN_STACKADJ_RTX, const0_rtx);
#endif

  around_label = gen_label_rtx ();
  emit_jump (around_label);

  emit_label (cfun->eh->ehr_label);
  clobber_return_register ();

#ifdef EH_RETURN_STACKADJ_RTX
  emit_move_insn (EH_RETURN_STACKADJ_RTX, cfun->eh->ehr_stackadj);
#endif

#ifdef HAVE_eh_return
  if (HAVE_eh_return)
    emit_insn (gen_eh_return (cfun->eh->ehr_handler));
  else
#endif
    {
#ifdef EH_RETURN_HANDLER_RTX
      emit_move_insn (EH_RETURN_HANDLER_RTX, cfun->eh->ehr_handler);
#else
      error ("__builtin_eh_return not supported on this target");
#endif
    }

  emit_label (around_label);
}