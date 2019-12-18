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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ current_function_decl ; 
 scalar_t__ decl_function_context (scalar_t__) ; 
 int /*<<< orphan*/  emit_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  label_rtx (scalar_t__) ; 

void
expand_goto (tree label)
{
#ifdef ENABLE_CHECKING
  /* Check for a nonlocal goto to a containing function.  Should have
     gotten translated to __builtin_nonlocal_goto.  */
  tree context = decl_function_context (label);
  gcc_assert (!context || context == current_function_decl);
#endif

  emit_jump (label_rtx (label));
}