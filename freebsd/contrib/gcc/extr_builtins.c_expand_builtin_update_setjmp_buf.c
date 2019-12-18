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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {TYPE_1__* operand; } ;
struct TYPE_3__ {int mode; } ;

/* Variables and functions */
 scalar_t__ CODE_FOR_save_stack_nonlocal ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ HAVE_save_stack_nonlocal ; 
 scalar_t__ HAVE_setjmp ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int Pmode ; 
 int /*<<< orphan*/  SAVE_NONLOCAL ; 
 int STACK_SAVEAREA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_stack_save (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_setjmp () ; 
 TYPE_2__* insn_data ; 
 int /*<<< orphan*/  memory_address (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
expand_builtin_update_setjmp_buf (rtx buf_addr)
{
  enum machine_mode sa_mode = Pmode;
  rtx stack_save;


#ifdef HAVE_save_stack_nonlocal
  if (HAVE_save_stack_nonlocal)
    sa_mode = insn_data[(int) CODE_FOR_save_stack_nonlocal].operand[0].mode;
#endif
#ifdef STACK_SAVEAREA_MODE
  sa_mode = STACK_SAVEAREA_MODE (SAVE_NONLOCAL);
#endif

  stack_save
    = gen_rtx_MEM (sa_mode,
		   memory_address
		   (sa_mode,
		    plus_constant (buf_addr, 2 * GET_MODE_SIZE (Pmode))));

#ifdef HAVE_setjmp
  if (HAVE_setjmp)
    emit_insn (gen_setjmp ());
#endif

  emit_stack_save (SAVE_NONLOCAL, &stack_save, NULL_RTX);
}