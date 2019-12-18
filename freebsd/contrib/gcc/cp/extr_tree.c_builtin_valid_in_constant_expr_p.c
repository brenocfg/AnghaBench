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
 int DECL_IS_BUILTIN_CONSTANT_P (int /*<<< orphan*/ ) ; 

bool
builtin_valid_in_constant_expr_p (tree decl)
{
  /* At present BUILT_IN_CONSTANT_P is the only builtin we're allowing
     in constant-expressions.  We may want to add other builtins later. */
  return DECL_IS_BUILTIN_CONSTANT_P (decl);
}