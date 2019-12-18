#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__* elts; int len; } ;

/* Variables and functions */
 scalar_t__ ANON_AGGR_TYPE_P (scalar_t__) ; 
 scalar_t__ BOUND_TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ DECL_CLASS_TEMPLATE_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_DEPENDENT_P (scalar_t__) ; 
 scalar_t__ DECL_LANG_SPECIFIC (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 TYPE_1__* DECL_SORTED_FIELDS (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPENAME_TYPE ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 scalar_t__ TYPE_POLYMORPHIC_P (scalar_t__) ; 
 scalar_t__ TYPE_VFIELD (scalar_t__) ; 
 scalar_t__ USING_DECL ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_calls_lookup_field_1 ; 
 int /*<<< orphan*/  n_fields_searched ; 
 scalar_t__ vptr_identifier ; 

tree
lookup_field_1 (tree type, tree name, bool want_type)
{
  tree field;

  if (TREE_CODE (type) == TEMPLATE_TYPE_PARM
      || TREE_CODE (type) == BOUND_TEMPLATE_TEMPLATE_PARM
      || TREE_CODE (type) == TYPENAME_TYPE)
    /* The TYPE_FIELDS of a TEMPLATE_TYPE_PARM and
       BOUND_TEMPLATE_TEMPLATE_PARM are not fields at all;
       instead TYPE_FIELDS is the TEMPLATE_PARM_INDEX.  (Miraculously,
       the code often worked even when we treated the index as a list
       of fields!)
       The TYPE_FIELDS of TYPENAME_TYPE is its TYPENAME_TYPE_FULLNAME.  */
    return NULL_TREE;

  if (TYPE_NAME (type)
      && DECL_LANG_SPECIFIC (TYPE_NAME (type))
      && DECL_SORTED_FIELDS (TYPE_NAME (type)))
    {
      tree *fields = &DECL_SORTED_FIELDS (TYPE_NAME (type))->elts[0];
      int lo = 0, hi = DECL_SORTED_FIELDS (TYPE_NAME (type))->len;
      int i;

      while (lo < hi)
	{
	  i = (lo + hi) / 2;

#ifdef GATHER_STATISTICS
	  n_fields_searched++;
#endif /* GATHER_STATISTICS */

	  if (DECL_NAME (fields[i]) > name)
	    hi = i;
	  else if (DECL_NAME (fields[i]) < name)
	    lo = i + 1;
	  else
	    {
	      field = NULL_TREE;

	      /* We might have a nested class and a field with the
		 same name; we sorted them appropriately via
		 field_decl_cmp, so just look for the first or last
		 field with this name.  */
	      if (want_type)
		{
		  do
		    field = fields[i--];
		  while (i >= lo && DECL_NAME (fields[i]) == name);
		  if (TREE_CODE (field) != TYPE_DECL
		      && !DECL_CLASS_TEMPLATE_P (field))
		    field = NULL_TREE;
		}
	      else
		{
		  do
		    field = fields[i++];
		  while (i < hi && DECL_NAME (fields[i]) == name);
		}
	      return field;
	    }
	}
      return NULL_TREE;
    }

  field = TYPE_FIELDS (type);

#ifdef GATHER_STATISTICS
  n_calls_lookup_field_1++;
#endif /* GATHER_STATISTICS */
  for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
    {
#ifdef GATHER_STATISTICS
      n_fields_searched++;
#endif /* GATHER_STATISTICS */
      gcc_assert (DECL_P (field));
      if (DECL_NAME (field) == NULL_TREE
	  && ANON_AGGR_TYPE_P (TREE_TYPE (field)))
	{
	  tree temp = lookup_field_1 (TREE_TYPE (field), name, want_type);
	  if (temp)
	    return temp;
	}
      if (TREE_CODE (field) == USING_DECL)
	{
	  /* We generally treat class-scope using-declarations as
	     ARM-style access specifications, because support for the
	     ISO semantics has not been implemented.  So, in general,
	     there's no reason to return a USING_DECL, and the rest of
	     the compiler cannot handle that.  Once the class is
	     defined, USING_DECLs are purged from TYPE_FIELDS; see
	     handle_using_decl.  However, we make special efforts to
	     make using-declarations in class templates and class
	     template partial specializations work correctly.  */
	  if (!DECL_DEPENDENT_P (field))
	    continue;
	}

      if (DECL_NAME (field) == name
	  && (!want_type
	      || TREE_CODE (field) == TYPE_DECL
	      || DECL_CLASS_TEMPLATE_P (field)))
	return field;
    }
  /* Not found.  */
  if (name == vptr_identifier)
    {
      /* Give the user what s/he thinks s/he wants.  */
      if (TYPE_POLYMORPHIC_P (type))
	return TYPE_VFIELD (type);
    }
  return NULL_TREE;
}