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

/* Variables and functions */
 scalar_t__ HAVE_trap ; 
 int /*<<< orphan*/  LCT_NORETURN ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  abort_libfunc ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_trap () ; 

void
expand_builtin_trap (void)
{
#ifdef HAVE_trap
  if (HAVE_trap)
    emit_insn (gen_trap ());
  else
#endif
    emit_library_call (abort_libfunc, LCT_NORETURN, VOIDmode, 0);
  emit_barrier ();
}