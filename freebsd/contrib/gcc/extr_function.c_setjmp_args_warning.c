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
 scalar_t__ DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_RTL (scalar_t__) ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ regno_clobbered_at_setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
setjmp_args_warning (void)
{
  tree decl;
  for (decl = DECL_ARGUMENTS (current_function_decl);
       decl; decl = TREE_CHAIN (decl))
    if (DECL_RTL (decl) != 0
	&& REG_P (DECL_RTL (decl))
	&& regno_clobbered_at_setjmp (REGNO (DECL_RTL (decl))))
      warning (0, "argument %q+D might be clobbered by %<longjmp%> or %<vfork%>",
	       decl);
}