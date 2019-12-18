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
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 int /*<<< orphan*/  COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_COPY_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FIELD_DECL ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wextra ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_NEEDS_CONSTRUCTING (int /*<<< orphan*/ ) ; 
 scalar_t__ build_base_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  build_indirect_ref (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  construct_virtual_base (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  current_class_ptr ; 
 int /*<<< orphan*/  current_class_type ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  expand_aggr_init_1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_cleanup_for_base (scalar_t__,scalar_t__) ; 
 scalar_t__ extra_warnings ; 
 int in_base_initializer ; 
 int /*<<< orphan*/  initialize_vtbl_ptrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perform_member_init (scalar_t__,scalar_t__) ; 
 scalar_t__ sort_mem_initializers (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ void_type_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
emit_mem_initializers (tree mem_inits)
{
  /* We will already have issued an error message about the fact that
     the type is incomplete.  */
  if (!COMPLETE_TYPE_P (current_class_type))
    return;

  /* Sort the mem-initializers into the order in which the
     initializations should be performed.  */
  mem_inits = sort_mem_initializers (current_class_type, mem_inits);

  in_base_initializer = 1;

  /* Initialize base classes.  */
  while (mem_inits
	 && TREE_CODE (TREE_PURPOSE (mem_inits)) != FIELD_DECL)
    {
      tree subobject = TREE_PURPOSE (mem_inits);
      tree arguments = TREE_VALUE (mem_inits);

      /* If these initializations are taking place in a copy
	 constructor, the base class should probably be explicitly
	 initialized.  */
      if (extra_warnings && !arguments
	  && DECL_COPY_CONSTRUCTOR_P (current_function_decl)
	  && TYPE_NEEDS_CONSTRUCTING (BINFO_TYPE (subobject)))
	warning (OPT_Wextra, "%Jbase class %q#T should be explicitly initialized in the "
		 "copy constructor",
		 current_function_decl, BINFO_TYPE (subobject));

      /* If an explicit -- but empty -- initializer list was present,
	 treat it just like default initialization at this point.  */
      if (arguments == void_type_node)
	arguments = NULL_TREE;

      /* Initialize the base.  */
      if (BINFO_VIRTUAL_P (subobject))
	construct_virtual_base (subobject, arguments);
      else
	{
	  tree base_addr;

	  base_addr = build_base_path (PLUS_EXPR, current_class_ptr,
				       subobject, 1);
	  expand_aggr_init_1 (subobject, NULL_TREE,
			      build_indirect_ref (base_addr, NULL),
			      arguments,
			      LOOKUP_NORMAL);
	  expand_cleanup_for_base (subobject, NULL_TREE);
	}

      mem_inits = TREE_CHAIN (mem_inits);
    }
  in_base_initializer = 0;

  /* Initialize the vptrs.  */
  initialize_vtbl_ptrs (current_class_ptr);

  /* Initialize the data members.  */
  while (mem_inits)
    {
      perform_member_init (TREE_PURPOSE (mem_inits),
			   TREE_VALUE (mem_inits));
      mem_inits = TREE_CHAIN (mem_inits);
    }
}