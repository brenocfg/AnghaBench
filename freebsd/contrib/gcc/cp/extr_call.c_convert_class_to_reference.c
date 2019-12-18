#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct z_candidate {int viable; TYPE_2__* second_conv; scalar_t__ fn; scalar_t__ args; TYPE_1__** convs; struct z_candidate* next; } ;
struct TYPE_13__ {int bad_p; struct z_candidate* cand; } ;
typedef  TYPE_2__ conversion ;
struct TYPE_12__ {int bad_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEDUCE_CONV ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_BINFO (scalar_t__) ; 
 struct z_candidate* add_function_candidate (struct z_candidate**,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct z_candidate* add_template_candidate (struct z_candidate**,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* build_conv (int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 
 TYPE_2__* build_identity_conv (scalar_t__,scalar_t__) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ build_reference_type (scalar_t__) ; 
 int /*<<< orphan*/  build_this (scalar_t__) ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ck_user ; 
 TYPE_2__* direct_reference_binding (scalar_t__,TYPE_2__*) ; 
 scalar_t__ lookup_conversions (scalar_t__) ; 
 TYPE_2__* merge_conversion_sequences (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pedantic ; 
 scalar_t__ reference_compatible_p (scalar_t__,scalar_t__) ; 
 struct z_candidate* splice_viable (struct z_candidate*,int /*<<< orphan*/ ,int*) ; 
 struct z_candidate* tourney (struct z_candidate*) ; 
 scalar_t__ tree_cons (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static conversion *
convert_class_to_reference (tree t, tree s, tree expr)
{
  tree conversions;
  tree arglist;
  conversion *conv;
  tree reference_type;
  struct z_candidate *candidates;
  struct z_candidate *cand;
  bool any_viable_p;

  conversions = lookup_conversions (s);
  if (!conversions)
    return NULL;

  /* [over.match.ref]

     Assuming that "cv1 T" is the underlying type of the reference
     being initialized, and "cv S" is the type of the initializer
     expression, with S a class type, the candidate functions are
     selected as follows:

     --The conversion functions of S and its base classes are
       considered.  Those that are not hidden within S and yield type
       "reference to cv2 T2", where "cv1 T" is reference-compatible
       (_dcl.init.ref_) with "cv2 T2", are candidate functions.

     The argument list has one argument, which is the initializer
     expression.  */

  candidates = 0;

  /* Conceptually, we should take the address of EXPR and put it in
     the argument list.  Unfortunately, however, that can result in
     error messages, which we should not issue now because we are just
     trying to find a conversion operator.  Therefore, we use NULL,
     cast to the appropriate type.  */
  arglist = build_int_cst (build_pointer_type (s), 0);
  arglist = build_tree_list (NULL_TREE, arglist);

  reference_type = build_reference_type (t);

  while (conversions)
    {
      tree fns = TREE_VALUE (conversions);

      for (; fns; fns = OVL_NEXT (fns))
	{
	  tree f = OVL_CURRENT (fns);
	  tree t2 = TREE_TYPE (TREE_TYPE (f));

	  cand = NULL;

	  /* If this is a template function, try to get an exact
	     match.  */
	  if (TREE_CODE (f) == TEMPLATE_DECL)
	    {
	      cand = add_template_candidate (&candidates,
					     f, s,
					     NULL_TREE,
					     arglist,
					     reference_type,
					     TYPE_BINFO (s),
					     TREE_PURPOSE (conversions),
					     LOOKUP_NORMAL,
					     DEDUCE_CONV);

	      if (cand)
		{
		  /* Now, see if the conversion function really returns
		     an lvalue of the appropriate type.  From the
		     point of view of unification, simply returning an
		     rvalue of the right type is good enough.  */
		  f = cand->fn;
		  t2 = TREE_TYPE (TREE_TYPE (f));
		  if (TREE_CODE (t2) != REFERENCE_TYPE
		      || !reference_compatible_p (t, TREE_TYPE (t2)))
		    {
		      candidates = candidates->next;
		      cand = NULL;
		    }
		}
	    }
	  else if (TREE_CODE (t2) == REFERENCE_TYPE
		   && reference_compatible_p (t, TREE_TYPE (t2)))
	    cand = add_function_candidate (&candidates, f, s, arglist,
					   TYPE_BINFO (s),
					   TREE_PURPOSE (conversions),
					   LOOKUP_NORMAL);

	  if (cand)
	    {
	      conversion *identity_conv;
	      /* Build a standard conversion sequence indicating the
		 binding from the reference type returned by the
		 function to the desired REFERENCE_TYPE.  */
	      identity_conv
		= build_identity_conv (TREE_TYPE (TREE_TYPE
						  (TREE_TYPE (cand->fn))),
				       NULL_TREE);
	      cand->second_conv
		= (direct_reference_binding
		   (reference_type, identity_conv));
	      cand->second_conv->bad_p |= cand->convs[0]->bad_p;
	    }
	}
      conversions = TREE_CHAIN (conversions);
    }

  candidates = splice_viable (candidates, pedantic, &any_viable_p);
  /* If none of the conversion functions worked out, let our caller
     know.  */
  if (!any_viable_p)
    return NULL;

  cand = tourney (candidates);
  if (!cand)
    return NULL;

  /* Now that we know that this is the function we're going to use fix
     the dummy first argument.  */
  cand->args = tree_cons (NULL_TREE,
			  build_this (expr),
			  TREE_CHAIN (cand->args));

  /* Build a user-defined conversion sequence representing the
     conversion.  */
  conv = build_conv (ck_user,
		     TREE_TYPE (TREE_TYPE (cand->fn)),
		     build_identity_conv (TREE_TYPE (expr), expr));
  conv->cand = cand;

  /* Merge it with the standard conversion sequence from the
     conversion function's return type to the desired type.  */
  cand->second_conv = merge_conversion_sequences (conv, cand->second_conv);

  if (cand->viable == -1)
    conv->bad_p = true;

  return cand->second_conv;
}