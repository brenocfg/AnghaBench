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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
determine_common_wider_type (tree *a, tree *b)
{
  tree wider_type = NULL;
  tree suba, subb;
  tree atype = TREE_TYPE (*a);

  if ((TREE_CODE (*a) == NOP_EXPR
       || TREE_CODE (*a) == CONVERT_EXPR))
    {
      suba = TREE_OPERAND (*a, 0);
      wider_type = TREE_TYPE (suba);
      if (TYPE_PRECISION (wider_type) < TYPE_PRECISION (atype))
	return atype;
    }
  else
    return atype;

  if ((TREE_CODE (*b) == NOP_EXPR
       || TREE_CODE (*b) == CONVERT_EXPR))
    {
      subb = TREE_OPERAND (*b, 0);
      if (TYPE_PRECISION (wider_type) != TYPE_PRECISION (TREE_TYPE (subb)))
	return atype;
    }
  else
    return atype;

  *a = suba;
  *b = subb;
  return wider_type;
}