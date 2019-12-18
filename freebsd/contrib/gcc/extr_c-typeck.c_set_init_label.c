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
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ constructor_fields ; 
 scalar_t__ constructor_range_stack ; 
 int /*<<< orphan*/  constructor_type ; 
 int /*<<< orphan*/  designator_depth ; 
 int designator_erroneous ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  error_init (char*) ; 
 scalar_t__ lookup_field (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  push_range_stack (scalar_t__) ; 
 scalar_t__ set_designator (int /*<<< orphan*/ ) ; 

void
set_init_label (tree fieldname)
{
  tree anon = NULL_TREE;
  tree tail;

  if (set_designator (0))
    return;

  designator_erroneous = 1;

  if (TREE_CODE (constructor_type) != RECORD_TYPE
      && TREE_CODE (constructor_type) != UNION_TYPE)
    {
      error_init ("field name not in record or union initializer");
      return;
    }

  for (tail = TYPE_FIELDS (constructor_type); tail;
       tail = TREE_CHAIN (tail))
    {
      if (DECL_NAME (tail) == NULL_TREE
	  && (TREE_CODE (TREE_TYPE (tail)) == RECORD_TYPE
	      || TREE_CODE (TREE_TYPE (tail)) == UNION_TYPE))
	{
	  anon = lookup_field (tail, fieldname);
	  if (anon)
	    break;
	}

      if (DECL_NAME (tail) == fieldname)
	break;
    }

  if (tail == 0)
    error ("unknown field %qE specified in initializer", fieldname);

  while (tail)
    {
      constructor_fields = tail;
      designator_depth++;
      designator_erroneous = 0;
      if (constructor_range_stack)
	push_range_stack (NULL_TREE);

      if (anon)
	{
	  if (set_designator (0))
	    return;
	  tail = TREE_VALUE(anon);
	  anon = TREE_CHAIN(anon);
	}
      else
	tail = NULL_TREE;
    }
}