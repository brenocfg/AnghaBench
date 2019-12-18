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
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TRAMPOLINE_ADJUST_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_trampoline_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_adjust_trampoline (tree arglist)
{
  rtx tramp;

  if (!validate_arglist (arglist, POINTER_TYPE, VOID_TYPE))
    return NULL_RTX;

  tramp = expand_normal (TREE_VALUE (arglist));
  tramp = round_trampoline_addr (tramp);
#ifdef TRAMPOLINE_ADJUST_ADDRESS
  TRAMPOLINE_ADJUST_ADDRESS (tramp);
#endif

  return tramp;
}