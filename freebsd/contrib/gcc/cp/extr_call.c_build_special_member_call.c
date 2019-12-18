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
 int BINFO_SUBVTT_INDEX (scalar_t__) ; 
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 scalar_t__ CLASSTYPE_VBASECLASSES (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_VTABLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ ansi_assopname (int /*<<< orphan*/ ) ; 
 scalar_t__ base_ctor_identifier ; 
 scalar_t__ base_dtor_identifier ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_base_path (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ build_new_method_call (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ complete_ctor_identifier ; 
 scalar_t__ complete_dtor_identifier ; 
 int /*<<< orphan*/  complete_type_or_else (scalar_t__,scalar_t__) ; 
 scalar_t__ convert_to_base_statically (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  current_class_type ; 
 scalar_t__ current_in_charge_parm ; 
 int /*<<< orphan*/  current_vtt_parm ; 
 scalar_t__ decay_conversion (scalar_t__) ; 
 scalar_t__ deleting_dtor_identifier ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int integer_zero_node ; 
 scalar_t__ lookup_fnfields (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  same_type_ignoring_top_level_qualifiers_p (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 

tree
build_special_member_call (tree instance, tree name, tree args,
			   tree binfo, int flags)
{
  tree fns;
  /* The type of the subobject to be constructed or destroyed.  */
  tree class_type;

  gcc_assert (name == complete_ctor_identifier
	      || name == base_ctor_identifier
	      || name == complete_dtor_identifier
	      || name == base_dtor_identifier
	      || name == deleting_dtor_identifier
	      || name == ansi_assopname (NOP_EXPR));
  if (TYPE_P (binfo))
    {
      /* Resolve the name.  */
      if (!complete_type_or_else (binfo, NULL_TREE))
	return error_mark_node;

      binfo = TYPE_BINFO (binfo);
    }

  gcc_assert (binfo != NULL_TREE);

  class_type = BINFO_TYPE (binfo);

  /* Handle the special case where INSTANCE is NULL_TREE.  */
  if (name == complete_ctor_identifier && !instance)
    {
      instance = build_int_cst (build_pointer_type (class_type), 0);
      instance = build1 (INDIRECT_REF, class_type, instance);
    }
  else
    {
      if (name == complete_dtor_identifier
	  || name == base_dtor_identifier
	  || name == deleting_dtor_identifier)
	gcc_assert (args == NULL_TREE);

      /* Convert to the base class, if necessary.  */
      if (!same_type_ignoring_top_level_qualifiers_p
	  (TREE_TYPE (instance), BINFO_TYPE (binfo)))
	{
	  if (name != ansi_assopname (NOP_EXPR))
	    /* For constructors and destructors, either the base is
	       non-virtual, or it is virtual but we are doing the
	       conversion from a constructor or destructor for the
	       complete object.  In either case, we can convert
	       statically.  */
	    instance = convert_to_base_statically (instance, binfo);
	  else
	    /* However, for assignment operators, we must convert
	       dynamically if the base is virtual.  */
	    instance = build_base_path (PLUS_EXPR, instance,
					binfo, /*nonnull=*/1);
	}
    }

  gcc_assert (instance != NULL_TREE);

  fns = lookup_fnfields (binfo, name, 1);

  /* When making a call to a constructor or destructor for a subobject
     that uses virtual base classes, pass down a pointer to a VTT for
     the subobject.  */
  if ((name == base_ctor_identifier
       || name == base_dtor_identifier)
      && CLASSTYPE_VBASECLASSES (class_type))
    {
      tree vtt;
      tree sub_vtt;

      /* If the current function is a complete object constructor
	 or destructor, then we fetch the VTT directly.
	 Otherwise, we look it up using the VTT we were given.  */
      vtt = TREE_CHAIN (CLASSTYPE_VTABLES (current_class_type));
      vtt = decay_conversion (vtt);
      vtt = build3 (COND_EXPR, TREE_TYPE (vtt),
		    build2 (EQ_EXPR, boolean_type_node,
			    current_in_charge_parm, integer_zero_node),
		    current_vtt_parm,
		    vtt);
      gcc_assert (BINFO_SUBVTT_INDEX (binfo));
      sub_vtt = build2 (PLUS_EXPR, TREE_TYPE (vtt), vtt,
			BINFO_SUBVTT_INDEX (binfo));

      args = tree_cons (NULL_TREE, sub_vtt, args);
    }

  return build_new_method_call (instance, fns, args,
				TYPE_BINFO (BINFO_TYPE (binfo)),
				flags, /*fn=*/NULL);
}