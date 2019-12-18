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
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_mark_addressable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_mark_node ; 
 scalar_t__ error_operand_p (int /*<<< orphan*/ ) ; 

tree
build_address (tree t)
{
  tree addr;

  if (error_operand_p (t) || !cxx_mark_addressable (t))
    return error_mark_node;

  addr = build1 (ADDR_EXPR, build_pointer_type (TREE_TYPE (t)), t);

  return addr;
}