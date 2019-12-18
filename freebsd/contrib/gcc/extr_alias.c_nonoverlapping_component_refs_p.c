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
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  DECL_FIELD_CONTEXT (scalar_t__) ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nonoverlapping_component_refs_p (tree x, tree y)
{
  tree fieldx, fieldy, typex, typey, orig_y;

  do
    {
      /* The comparison has to be done at a common type, since we don't
	 know how the inheritance hierarchy works.  */
      orig_y = y;
      do
	{
	  fieldx = TREE_OPERAND (x, 1);
	  typex = TYPE_MAIN_VARIANT (DECL_FIELD_CONTEXT (fieldx));

	  y = orig_y;
	  do
	    {
	      fieldy = TREE_OPERAND (y, 1);
	      typey = TYPE_MAIN_VARIANT (DECL_FIELD_CONTEXT (fieldy));

	      if (typex == typey)
		goto found;

	      y = TREE_OPERAND (y, 0);
	    }
	  while (y && TREE_CODE (y) == COMPONENT_REF);

	  x = TREE_OPERAND (x, 0);
	}
      while (x && TREE_CODE (x) == COMPONENT_REF);
      /* Never found a common type.  */
      return false;

    found:
      /* If we're left with accessing different fields of a structure,
	 then no overlap.  */
      if (TREE_CODE (typex) == RECORD_TYPE
	  && fieldx != fieldy)
	return true;

      /* The comparison on the current field failed.  If we're accessing
	 a very nested structure, look at the next outer level.  */
      x = TREE_OPERAND (x, 0);
      y = TREE_OPERAND (y, 0);
    }
  while (x && y
	 && TREE_CODE (x) == COMPONENT_REF
	 && TREE_CODE (y) == COMPONENT_REF);

  return false;
}