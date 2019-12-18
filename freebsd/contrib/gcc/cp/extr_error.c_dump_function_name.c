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
 scalar_t__ DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CONV_FN_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FRIEND_PSEUDO_TEMPLATE_INSTANTIATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_LANG_SPECIFIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_TEMPLATE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TI_TEMPLATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_USE_TEMPLATE (int /*<<< orphan*/ ) ; 
 scalar_t__ IDENTIFIER_OPNAME_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PRIMARY_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMPLATE_DECL ; 
 int TFF_PLAIN_IDENTIFIER ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constructor_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_decl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_template_parms (scalar_t__,int,int) ; 
 int /*<<< orphan*/  dump_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_cxx_complement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_cxx_tree_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_function_name (tree t, int flags)
{
  tree name = DECL_NAME (t);

  /* We can get here with a decl that was synthesized by language-
     independent machinery (e.g. coverage.c) in which case it won't
     have a lang_specific structure attached and DECL_CONSTRUCTOR_P
     will crash.  In this case it is safe just to print out the
     literal name.  */
  if (!DECL_LANG_SPECIFIC (t))
    {
      pp_cxx_tree_identifier (cxx_pp, name);
      return;
    }

  if (TREE_CODE (t) == TEMPLATE_DECL)
    t = DECL_TEMPLATE_RESULT (t);

  /* Don't let the user see __comp_ctor et al.  */
  if (DECL_CONSTRUCTOR_P (t)
      || DECL_DESTRUCTOR_P (t))
    name = constructor_name (DECL_CONTEXT (t));

  if (DECL_DESTRUCTOR_P (t))
    {
      pp_cxx_complement (cxx_pp);
      dump_decl (name, TFF_PLAIN_IDENTIFIER);
    }
  else if (DECL_CONV_FN_P (t))
    {
      /* This cannot use the hack that the operator's return
	 type is stashed off of its name because it may be
	 used for error reporting.  In the case of conflicting
	 declarations, both will have the same name, yet
	 the types will be different, hence the TREE_TYPE field
	 of the first name will be clobbered by the second.  */
      pp_cxx_identifier (cxx_pp, "operator");
      dump_type (TREE_TYPE (TREE_TYPE (t)), flags);
    }
  else if (IDENTIFIER_OPNAME_P (name))
    pp_cxx_tree_identifier (cxx_pp, name);
  else
    dump_decl (name, flags);

  if (DECL_TEMPLATE_INFO (t)
      && !DECL_FRIEND_PSEUDO_TEMPLATE_INSTANTIATION (t)
      && (TREE_CODE (DECL_TI_TEMPLATE (t)) != TEMPLATE_DECL
	  || PRIMARY_TEMPLATE_P (DECL_TI_TEMPLATE (t))))
    dump_template_parms (DECL_TEMPLATE_INFO (t), !DECL_USE_TEMPLATE (t), flags);
}