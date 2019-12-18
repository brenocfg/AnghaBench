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
typedef  scalar_t__ tag_scope ;
typedef  enum tag_types { ____Placeholder_tag_types } tag_types ;

/* Variables and functions */
 scalar_t__ DECL_CLASS_TEMPLATE_P (scalar_t__) ; 
 int DECL_SELF_REFERENCE_P (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_RESULT (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_LIST ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ check_elaborated_type_specifier (int,scalar_t__,int) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ lookup_name_prefer_type (scalar_t__,int) ; 
 scalar_t__ lookup_type_scope (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  print_candidates (scalar_t__) ; 
 scalar_t__ ts_current ; 
 scalar_t__ ts_global ; 
 scalar_t__ ts_within_enclosing_non_class ; 

__attribute__((used)) static tree
lookup_and_check_tag (enum tag_types tag_code, tree name,
		      tag_scope scope, bool template_header_p)
{
  tree t;
  tree decl;
  if (scope == ts_global)
    {
      /* First try ordinary name lookup, ignoring hidden class name
	 injected via friend declaration.  */
      decl = lookup_name_prefer_type (name, 2);
      /* If that fails, the name will be placed in the smallest
	 non-class, non-function-prototype scope according to 3.3.1/5.
	 We may already have a hidden name declared as friend in this
	 scope.  So lookup again but not ignoring hidden names.
	 If we find one, that name will be made visible rather than
	 creating a new tag.  */
      if (!decl)
	decl = lookup_type_scope (name, ts_within_enclosing_non_class);
    }
  else
    decl = lookup_type_scope (name, scope);

  if (decl && DECL_CLASS_TEMPLATE_P (decl))
    decl = DECL_TEMPLATE_RESULT (decl);

  if (decl && TREE_CODE (decl) == TYPE_DECL)
    {
      /* Look for invalid nested type:
	   class C {
	     class C {};
	   };  */
      if (scope == ts_current && DECL_SELF_REFERENCE_P (decl))
	{
	  error ("%qD has the same name as the class in which it is "
		 "declared",
		 decl);
	  return error_mark_node;
	}

      /* Two cases we need to consider when deciding if a class
	 template is allowed as an elaborated type specifier:
	 1. It is a self reference to its own class.
	 2. It comes with a template header.

	 For example:

	   template <class T> class C {
	     class C *c1;		// DECL_SELF_REFERENCE_P is true
	     class D;
	   };
	   template <class U> class C; // template_header_p is true
	   template <class T> class C<T>::D {
	     class C *c2;		// DECL_SELF_REFERENCE_P is true
	   };  */

      t = check_elaborated_type_specifier (tag_code,
					   decl,
					   template_header_p
					   | DECL_SELF_REFERENCE_P (decl));
      return t;
    }
  else if (decl && TREE_CODE (decl) == TREE_LIST)
    {
      error ("reference to %qD is ambiguous", name);
      print_candidates (decl);
      return error_mark_node;
    }
  else
    return NULL_TREE;
}