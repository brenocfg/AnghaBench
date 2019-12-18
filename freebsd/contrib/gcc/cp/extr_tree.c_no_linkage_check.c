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

/* Variables and functions */
#define  ARRAY_TYPE 136 
 int /*<<< orphan*/  CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
#define  ENUMERAL_TYPE 135 
#define  FUNCTION_TYPE 134 
#define  METHOD_TYPE 133 
 int /*<<< orphan*/  NULL_TREE ; 
#define  OFFSET_TYPE 132 
#define  POINTER_TYPE 131 
#define  RECORD_TYPE 130 
#define  REFERENCE_TYPE 129 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ANONYMOUS_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_METHOD_BASETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 128 
 int /*<<< orphan*/  decl_function_context (int /*<<< orphan*/ ) ; 
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  void_list_node ; 

tree
no_linkage_check (tree t, bool relaxed_p)
{
  tree r;

  /* There's no point in checking linkage on template functions; we
     can't know their complete types.  */
  if (processing_template_decl)
    return NULL_TREE;

  switch (TREE_CODE (t))
    {
      tree fn;

    case RECORD_TYPE:
      if (TYPE_PTRMEMFUNC_P (t))
	goto ptrmem;
      /* Fall through.  */
    case UNION_TYPE:
      if (!CLASS_TYPE_P (t))
	return NULL_TREE;
      /* Fall through.  */
    case ENUMERAL_TYPE:
      if (TYPE_ANONYMOUS_P (t))
	return t;
      fn = decl_function_context (TYPE_MAIN_DECL (t));
      if (fn && (!relaxed_p || !TREE_PUBLIC (fn)))
	return t;
      return NULL_TREE;

    case ARRAY_TYPE:
    case POINTER_TYPE:
    case REFERENCE_TYPE:
      return no_linkage_check (TREE_TYPE (t), relaxed_p);

    case OFFSET_TYPE:
    ptrmem:
      r = no_linkage_check (TYPE_PTRMEM_POINTED_TO_TYPE (t),
			    relaxed_p);
      if (r)
	return r;
      return no_linkage_check (TYPE_PTRMEM_CLASS_TYPE (t), relaxed_p);

    case METHOD_TYPE:
      r = no_linkage_check (TYPE_METHOD_BASETYPE (t), relaxed_p);
      if (r)
	return r;
      /* Fall through.  */
    case FUNCTION_TYPE:
      {
	tree parm;
	for (parm = TYPE_ARG_TYPES (t);
	     parm && parm != void_list_node;
	     parm = TREE_CHAIN (parm))
	  {
	    r = no_linkage_check (TREE_VALUE (parm), relaxed_p);
	    if (r)
	      return r;
	  }
	return no_linkage_check (TREE_TYPE (t), relaxed_p);
      }

    default:
      return NULL_TREE;
    }
}