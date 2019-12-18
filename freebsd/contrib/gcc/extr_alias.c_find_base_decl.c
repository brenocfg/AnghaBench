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
 scalar_t__ DECL_BASED_ON_RESTRICT_P (scalar_t__) ; 
 scalar_t__ DECL_GET_RESTRICT_BASE (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TREE_CODE_CLASS (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ error_mark_node ; 
#define  tcc_binary 129 
#define  tcc_unary 128 

__attribute__((used)) static tree
find_base_decl (tree t)
{
  tree d0, d1;

  if (t == 0 || t == error_mark_node || ! POINTER_TYPE_P (TREE_TYPE (t)))
    return 0;

  /* If this is a declaration, return it.  If T is based on a restrict
     qualified decl, return that decl.  */
  if (DECL_P (t))
    {
      if (TREE_CODE (t) == VAR_DECL && DECL_BASED_ON_RESTRICT_P (t))
	t = DECL_GET_RESTRICT_BASE (t);
      return t;
    }

  /* Handle general expressions.  It would be nice to deal with
     COMPONENT_REFs here.  If we could tell that `a' and `b' were the
     same, then `a->f' and `b->f' are also the same.  */
  switch (TREE_CODE_CLASS (TREE_CODE (t)))
    {
    case tcc_unary:
      return find_base_decl (TREE_OPERAND (t, 0));

    case tcc_binary:
      /* Return 0 if found in neither or both are the same.  */
      d0 = find_base_decl (TREE_OPERAND (t, 0));
      d1 = find_base_decl (TREE_OPERAND (t, 1));
      if (d0 == d1)
	return d0;
      else if (d0 == 0)
	return d1;
      else if (d1 == 0)
	return d0;
      else
	return 0;

    default:
      return 0;
    }
}