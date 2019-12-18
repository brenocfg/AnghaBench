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
typedef  enum tree_code_class { ____Placeholder_tree_code_class } tree_code_class ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int IDENTIFIER_NODE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int tcc_exceptional ; 

tree
c_return_interface_record_type (tree typename)
{
  enum tree_code_class class;
  enum tree_code code;
  tree retval = NULL;

  if (typename == NULL)
      return retval;

  code = TREE_CODE (typename);
  class = TREE_CODE_CLASS (code);

  if (code != IDENTIFIER_NODE
      || class != tcc_exceptional)
      return retval;

  if (TREE_TYPE (typename)
      && TREE_CODE (TREE_TYPE (typename)) == RECORD_TYPE)
      retval = TREE_TYPE (typename);

  if (retval
      && TREE_CODE (retval) != RECORD_TYPE)
      retval = NULL;

  return retval;
}