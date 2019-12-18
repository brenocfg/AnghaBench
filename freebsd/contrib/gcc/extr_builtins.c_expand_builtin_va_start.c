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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  EXPAND_BUILTIN_VA_START (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expand_builtin_next_arg () ; 
 scalar_t__ fold_builtin_next_arg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stabilize_va_list (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  std_expand_builtin_va_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_va_start (tree arglist)
{
  rtx nextarg;
  tree chain, valist;

  chain = TREE_CHAIN (arglist);

  if (!chain)
    {
      error ("too few arguments to function %<va_start%>");
      return const0_rtx;
    }

  if (fold_builtin_next_arg (chain))
    return const0_rtx;

  nextarg = expand_builtin_next_arg ();
  valist = stabilize_va_list (TREE_VALUE (arglist), 1);

#ifdef EXPAND_BUILTIN_VA_START
  EXPAND_BUILTIN_VA_START (valist, nextarg);
#else
  std_expand_builtin_va_start (valist, nextarg);
#endif

  return const0_rtx;
}