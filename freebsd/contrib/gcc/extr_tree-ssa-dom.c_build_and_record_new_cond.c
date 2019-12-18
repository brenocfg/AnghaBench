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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  boolean_true_node ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
build_and_record_new_cond (enum tree_code new_code, tree op0, tree op1, tree *p)
{
  *p = build2 (new_code, boolean_type_node, op0, op1);
  p++;
  *p = boolean_true_node;
}