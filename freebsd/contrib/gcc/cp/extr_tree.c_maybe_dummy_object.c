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
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int ba_quiet ; 
 int ba_unique ; 
 scalar_t__ build_dummy_object (scalar_t__) ; 
 scalar_t__ build_x_arrow (scalar_t__) ; 
 scalar_t__ cur_block ; 
 scalar_t__ current_class_ref ; 
 scalar_t__ current_class_type ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ lookup_base (scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lookup_name (int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  this_identifier ; 

tree
maybe_dummy_object (tree type, tree* binfop)
{
  tree decl, context;
  tree binfo;

  if (current_class_type
      && (binfo = lookup_base (current_class_type, type,
			       ba_unique | ba_quiet, NULL)))
    context = current_class_type;
  else
    {
      /* Reference from a nested class member function.  */
      context = type;
      binfo = TYPE_BINFO (type);
    }

  if (binfop)
    *binfop = binfo;

  if (current_class_ref && context == current_class_type
      /* Kludge: Make sure that current_class_type is actually
	 correct.  It might not be if we're in the middle of
	 tsubst_default_argument.  */
      && same_type_p (TYPE_MAIN_VARIANT (TREE_TYPE (current_class_ref)),
		      current_class_type))
    decl = current_class_ref;
  /* APPLE LOCAL begin radar 6154598 */
    else if (cur_block)
    {
      tree this_copiedin_var = lookup_name (this_identifier);
      gcc_assert (!current_class_ref);
      gcc_assert (this_copiedin_var);
      decl = build_x_arrow (this_copiedin_var);
    }  
  /* APPLE LOCAL end radar 6154598 */
  else
    decl = build_dummy_object (context);

  return decl;
}