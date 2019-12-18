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
 int CONV_FORCE_TEMP ; 
 int CONV_IMPLICIT ; 
 scalar_t__ IS_AGGR_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ TARGET_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decay_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

tree
force_rvalue (tree expr)
{
  if (IS_AGGR_TYPE (TREE_TYPE (expr)) && TREE_CODE (expr) != TARGET_EXPR)
    expr = ocp_convert (TREE_TYPE (expr), expr,
			CONV_IMPLICIT|CONV_FORCE_TEMP, LOOKUP_NORMAL);
  else
    expr = decay_conversion (expr);

  return expr;
}