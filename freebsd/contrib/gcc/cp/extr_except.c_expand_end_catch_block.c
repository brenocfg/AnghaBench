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
 scalar_t__ DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_throw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  doing_eh (int) ; 
 int /*<<< orphan*/  finish_expr_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ in_function_try_handler ; 

void
expand_end_catch_block (void)
{
  if (! doing_eh (1))
    return;

  /* The exception being handled is rethrown if control reaches the end of
     a handler of the function-try-block of a constructor or destructor.  */
  if (in_function_try_handler
      && (DECL_CONSTRUCTOR_P (current_function_decl)
	  || DECL_DESTRUCTOR_P (current_function_decl)))
    finish_expr_stmt (build_throw (NULL_TREE));
}