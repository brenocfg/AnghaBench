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
 int SSA_VAR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ handled_component_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
var_decl_component_p (tree var)
{
  tree inner = var;
  while (handled_component_p (inner))
    inner = TREE_OPERAND (inner, 0);
  return SSA_VAR_P (inner);
}