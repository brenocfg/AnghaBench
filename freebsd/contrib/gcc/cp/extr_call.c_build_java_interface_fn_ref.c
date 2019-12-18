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
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  CALL_EXPR ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_VIRTUAL_P (scalar_t__) ; 
 int /*<<< orphan*/  NOT_BUILT_IN ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_METHODS (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_address (scalar_t__) ; 
 int /*<<< orphan*/  build_function_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_indirect_ref (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ build_tree_list (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_void_list_node () ; 
 scalar_t__ build_vtbl_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ builtin_function (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ java_iface_lookup_fn ; 
 scalar_t__ java_int_type_node ; 
 scalar_t__ lookup_field (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ptr_type_node ; 
 scalar_t__ tree_cons (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
build_java_interface_fn_ref (tree fn, tree instance)
{
  tree lookup_args, lookup_fn, method, idx;
  tree klass_ref, iface, iface_ref;
  int i;

  if (!java_iface_lookup_fn)
    {
      tree endlink = build_void_list_node ();
      tree t = tree_cons (NULL_TREE, ptr_type_node,
			  tree_cons (NULL_TREE, ptr_type_node,
				     tree_cons (NULL_TREE, java_int_type_node,
						endlink)));
      java_iface_lookup_fn
	= builtin_function ("_Jv_LookupInterfaceMethodIdx",
			    build_function_type (ptr_type_node, t),
			    0, NOT_BUILT_IN, NULL, NULL_TREE);
    }

  /* Look up the pointer to the runtime java.lang.Class object for `instance'.
     This is the first entry in the vtable.  */
  klass_ref = build_vtbl_ref (build_indirect_ref (instance, 0),
			      integer_zero_node);

  /* Get the java.lang.Class pointer for the interface being called.  */
  iface = DECL_CONTEXT (fn);
  iface_ref = lookup_field (iface, get_identifier ("class$"), 0, false);
  if (!iface_ref || TREE_CODE (iface_ref) != VAR_DECL
      || DECL_CONTEXT (iface_ref) != iface)
    {
      error ("could not find class$ field in java interface type %qT",
		iface);
      return error_mark_node;
    }
  iface_ref = build_address (iface_ref);
  iface_ref = convert (build_pointer_type (iface), iface_ref);

  /* Determine the itable index of FN.  */
  i = 1;
  for (method = TYPE_METHODS (iface); method; method = TREE_CHAIN (method))
    {
      if (!DECL_VIRTUAL_P (method))
	continue;
      if (fn == method)
	break;
      i++;
    }
  idx = build_int_cst (NULL_TREE, i);

  lookup_args = tree_cons (NULL_TREE, klass_ref,
			   tree_cons (NULL_TREE, iface_ref,
				      build_tree_list (NULL_TREE, idx)));
  lookup_fn = build1 (ADDR_EXPR,
		      build_pointer_type (TREE_TYPE (java_iface_lookup_fn)),
		      java_iface_lookup_fn);
  return build3 (CALL_EXPR, ptr_type_node, lookup_fn, lookup_args, NULL_TREE);
}