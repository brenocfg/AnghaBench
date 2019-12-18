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
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  fold_build_cleanup_point_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perform_implicit_conversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ processing_template_decl ; 

tree
condition_conversion (tree expr)
{
  tree t;
  if (processing_template_decl)
    return expr;
  t = perform_implicit_conversion (boolean_type_node, expr);
  t = fold_build_cleanup_point_expr (boolean_type_node, t);
  return t;
}