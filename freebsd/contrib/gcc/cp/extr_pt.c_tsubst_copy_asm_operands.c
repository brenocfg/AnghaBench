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
typedef  int /*<<< orphan*/  tsubst_flags_t ;
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/ * RECUR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_LIST ; 
 int /*<<< orphan*/ * TREE_PURPOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsubst_copy_and_build (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * void_list_node ; 
 int /*<<< orphan*/ * void_type_node ; 

__attribute__((used)) static tree
tsubst_copy_asm_operands (tree t, tree args, tsubst_flags_t complain,
			  tree in_decl)
{
#define RECUR(t) tsubst_copy_asm_operands (t, args, complain, in_decl)

  tree purpose, value, chain;

  if (t == NULL)
    return t;

  if (TREE_CODE (t) != TREE_LIST)
    return tsubst_copy_and_build (t, args, complain, in_decl,
				  /*function_p=*/false,
				  /*integral_constant_expression_p=*/false);

  if (t == void_list_node)
    return t;

  purpose = TREE_PURPOSE (t);
  if (purpose)
    purpose = RECUR (purpose);
  value = TREE_VALUE (t);
  if (value)
    value = RECUR (value);
  chain = TREE_CHAIN (t);
  if (chain && chain != void_type_node)
    chain = RECUR (chain);
  return tree_cons (purpose, value, chain);
#undef RECUR
}