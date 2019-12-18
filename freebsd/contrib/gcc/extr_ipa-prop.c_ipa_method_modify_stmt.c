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
struct cgraph_node {int dummy; } ;

/* Variables and functions */
#define  ASM_EXPR 129 
#define  MODIFY_EXPR 128 
 int PARM_DECL ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipa_method_formal_count (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipa_method_modify_set (struct cgraph_node*,int,int) ; 
 int ipa_method_tree_map (struct cgraph_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipa_method_modify_stmt (struct cgraph_node *mt, tree stmt)
{
  int i, j;

  switch (TREE_CODE (stmt))
    {
    case MODIFY_EXPR:
      if (TREE_CODE (TREE_OPERAND (stmt, 0)) == PARM_DECL)
	{
	  i = ipa_method_tree_map (mt, TREE_OPERAND (stmt, 0));
	  if (i >= 0)
            ipa_method_modify_set (mt, i, true);
	}
      break;
    case ASM_EXPR:
      /* Asm code could modify any of the parameters.  */
      for (j = 0; j < ipa_method_formal_count (mt); j++)
	ipa_method_modify_set (mt, j, true);
      break;
    default:
      break;
    }
}