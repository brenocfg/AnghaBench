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
 int POINTERS_EXTEND_UNSIGNED ; 
 int /*<<< orphan*/  convert_modes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_mode ; 
 int /*<<< orphan*/  word_mode ; 

rtx
expand_builtin_extend_pointer (tree addr_tree)
{
  rtx addr = expand_expr (addr_tree, NULL_RTX, ptr_mode, 0);
  int extend;

#ifdef POINTERS_EXTEND_UNSIGNED
  extend = POINTERS_EXTEND_UNSIGNED;
#else
  /* The previous EH code did an unsigned extend by default, so we do this also
     for consistency.  */
  extend = 1;
#endif

  return convert_modes (word_mode, ptr_mode, addr, extend);
}