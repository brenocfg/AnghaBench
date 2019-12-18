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
 int /*<<< orphan*/  default_def (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
arg_needs_copy_p (tree param)
{
  tree def;

  if (!is_gimple_reg (param) || !var_ann (param))
    return false;
		
  /* Parameters that are only defined but never used need not be copied.  */
  def = default_def (param);
  if (!def)
    return false;

  return true;
}