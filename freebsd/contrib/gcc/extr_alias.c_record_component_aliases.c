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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
#define  ARRAY_TYPE 132 
 int /*<<< orphan*/  BINFO_BASE_ITERATE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
#define  COMPLEX_TYPE 131 
 int /*<<< orphan*/  DECL_NONADDRESSABLE_P (int /*<<< orphan*/ ) ; 
 int FIELD_DECL ; 
#define  QUAL_UNION_TYPE 130 
#define  RECORD_TYPE 129 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_NONALIASED_COMPONENT (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 128 
 scalar_t__ get_alias_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_alias_subset (scalar_t__,scalar_t__) ; 

void
record_component_aliases (tree type)
{
  HOST_WIDE_INT superset = get_alias_set (type);
  tree field;

  if (superset == 0)
    return;

  switch (TREE_CODE (type))
    {
    case ARRAY_TYPE:
      if (! TYPE_NONALIASED_COMPONENT (type))
	record_alias_subset (superset, get_alias_set (TREE_TYPE (type)));
      break;

    case RECORD_TYPE:
    case UNION_TYPE:
    case QUAL_UNION_TYPE:
      /* Recursively record aliases for the base classes, if there are any.  */
      if (TYPE_BINFO (type))
	{
	  int i;
	  tree binfo, base_binfo;

	  for (binfo = TYPE_BINFO (type), i = 0;
	       BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
	    record_alias_subset (superset,
				 get_alias_set (BINFO_TYPE (base_binfo)));
	}
      for (field = TYPE_FIELDS (type); field != 0; field = TREE_CHAIN (field))
	if (TREE_CODE (field) == FIELD_DECL && ! DECL_NONADDRESSABLE_P (field))
	  record_alias_subset (superset, get_alias_set (TREE_TYPE (field)));
      break;

    case COMPLEX_TYPE:
      record_alias_subset (superset, get_alias_set (TREE_TYPE (type)));
      break;

    default:
      break;
    }
}