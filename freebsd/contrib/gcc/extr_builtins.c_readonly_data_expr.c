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
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ STRING_CST ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int decl_readonly_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_base_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
readonly_data_expr (tree exp)
{
  STRIP_NOPS (exp);

  if (TREE_CODE (exp) != ADDR_EXPR)
    return false;

  exp = get_base_address (TREE_OPERAND (exp, 0));
  if (!exp)
    return false;

  /* Make sure we call decl_readonly_section only for trees it
     can handle (since it returns true for everything it doesn't
     understand).  */
  if (TREE_CODE (exp) == STRING_CST
      || TREE_CODE (exp) == CONSTRUCTOR
      || (TREE_CODE (exp) == VAR_DECL && TREE_STATIC (exp)))
    return decl_readonly_section (exp, 0);
  else
    return false;
}