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
typedef  int /*<<< orphan*/  rtx ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 scalar_t__ INT_MEM_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ var_debug_decl (scalar_t__) ; 

__attribute__((used)) static bool
same_variable_part_p (rtx loc, tree expr, HOST_WIDE_INT offset)
{
  tree expr2;
  HOST_WIDE_INT offset2;

  if (! DECL_P (expr))
    return false;

  if (REG_P (loc))
    {
      expr2 = REG_EXPR (loc);
      offset2 = REG_OFFSET (loc);
    }
  else if (MEM_P (loc))
    {
      expr2 = MEM_EXPR (loc);
      offset2 = INT_MEM_OFFSET (loc);
    }
  else
    return false;

  if (! expr2 || ! DECL_P (expr2))
    return false;

  expr = var_debug_decl (expr);
  expr2 = var_debug_decl (expr2);

  return (expr == expr2 && offset == offset2);
}