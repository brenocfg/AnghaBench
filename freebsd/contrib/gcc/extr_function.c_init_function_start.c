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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_IS_BUILTIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTE_INSN_DELETED ; 
 int /*<<< orphan*/  OPT_Waggregate_return ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_line_note (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_note (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_function_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
init_function_start (tree subr)
{
  prepare_function_start (subr);

  /* Prevent ever trying to delete the first instruction of a
     function.  Also tell final how to output a linenum before the
     function prologue.  Note linenums could be missing, e.g. when
     compiling a Java .class file.  */
  if (! DECL_IS_BUILTIN (subr))
    emit_line_note (DECL_SOURCE_LOCATION (subr));

  /* Make sure first insn is a note even if we don't want linenums.
     This makes sure the first insn will never be deleted.
     Also, final expects a note to appear there.  */
  emit_note (NOTE_INSN_DELETED);

  /* Warn if this value is an aggregate type,
     regardless of which calling convention we are using for it.  */
  if (AGGREGATE_TYPE_P (TREE_TYPE (DECL_RESULT (subr))))
    warning (OPT_Waggregate_return, "function returns an aggregate");
}