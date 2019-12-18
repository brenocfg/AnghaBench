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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_type_class ; 
 int /*<<< orphan*/  type_to_class (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_classify_type (tree arglist)
{
  if (arglist == 0)
    return build_int_cst (NULL_TREE, no_type_class);

  return build_int_cst (NULL_TREE,
			type_to_class (TREE_TYPE (TREE_VALUE (arglist))));
}