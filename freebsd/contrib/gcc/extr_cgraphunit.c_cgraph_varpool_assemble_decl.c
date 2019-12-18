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
struct cgraph_varpool_node {int /*<<< orphan*/  alias; int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_HAS_VALUE_EXPR_P (int /*<<< orphan*/ ) ; 
 int TREE_ASM_WRITTEN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  assemble_variable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cgraph_varpool_assemble_decl (struct cgraph_varpool_node *node)
{
  tree decl = node->decl;

  if (!TREE_ASM_WRITTEN (decl)
      && !node->alias
      && !DECL_EXTERNAL (decl)
      && (TREE_CODE (decl) != VAR_DECL || !DECL_HAS_VALUE_EXPR_P (decl)))
    {
      assemble_variable (decl, 0, 1, 0);
      return TREE_ASM_WRITTEN (decl);
    }

  return false;
}