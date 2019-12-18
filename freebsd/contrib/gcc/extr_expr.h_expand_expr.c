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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum expand_modifier { ____Placeholder_expand_modifier } expand_modifier ;

/* Variables and functions */
 int /*<<< orphan*/  expand_expr_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline rtx
expand_expr (tree exp, rtx target, enum machine_mode mode,
	     enum expand_modifier modifier)
{
  return expand_expr_real (exp, target, mode, modifier, NULL);
}