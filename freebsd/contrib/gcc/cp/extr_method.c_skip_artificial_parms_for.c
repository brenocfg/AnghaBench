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
 scalar_t__ DECL_HAS_IN_CHARGE_PARM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_HAS_VTT_PARM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_FUNCTION_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 

tree
skip_artificial_parms_for (tree fn, tree list)
{
  if (DECL_NONSTATIC_MEMBER_FUNCTION_P (fn))
    list = TREE_CHAIN (list);
  else
    return list;

  if (DECL_HAS_IN_CHARGE_PARM_P (fn))
    list = TREE_CHAIN (list);
  if (DECL_HAS_VTT_PARM_P (fn))
    list = TREE_CHAIN (list);
  return list;
}