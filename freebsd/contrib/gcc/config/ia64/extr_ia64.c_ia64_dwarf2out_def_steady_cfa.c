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
 scalar_t__ ARG_POINTER_CFA_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_pointer_rtx ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  dwarf2out_def_cfa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  ia64_emit_deleted_label_after_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ ia64_initial_elimination_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

__attribute__((used)) static void
ia64_dwarf2out_def_steady_cfa (rtx insn)
{
  rtx fp = frame_pointer_needed
    ? hard_frame_pointer_rtx
    : stack_pointer_rtx;

  dwarf2out_def_cfa
    (ia64_emit_deleted_label_after_insn (insn),
     REGNO (fp),
     ia64_initial_elimination_offset
     (REGNO (arg_pointer_rtx), REGNO (fp))
     + ARG_POINTER_CFA_OFFSET (current_function_decl));
}