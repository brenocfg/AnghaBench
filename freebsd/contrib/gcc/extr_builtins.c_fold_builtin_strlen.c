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
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 scalar_t__ c_strlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ size_type_node ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_strlen (tree arglist)
{
  if (!validate_arglist (arglist, POINTER_TYPE, VOID_TYPE))
    return NULL_TREE;
  else
    {
      tree len = c_strlen (TREE_VALUE (arglist), 0);

      if (len)
	{
	  /* Convert from the internal "sizetype" type to "size_t".  */
	  if (size_type_node)
	    len = fold_convert (size_type_node, len);
	  return len;
	}

      return NULL_TREE;
    }
}