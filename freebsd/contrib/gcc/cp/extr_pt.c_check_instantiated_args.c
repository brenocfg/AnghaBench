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
typedef  int tsubst_flags_t ;
typedef  char* tree ;

/* Variables and functions */
 int DECL_NTPARMS (char*) ; 
 scalar_t__ INTEGRAL_OR_ENUMERATION_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_CONSTANT (char*) ; 
 scalar_t__ TREE_TYPE (char*) ; 
 char* TREE_VEC_ELT (char*,int) ; 
 scalar_t__ TYPE_ANONYMOUS_P (char*) ; 
 scalar_t__ TYPE_P (char*) ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 char* no_linkage_check (char*,int) ; 
 int tf_error ; 
 scalar_t__ variably_modified_type_p (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
check_instantiated_args (tree tmpl, tree args, tsubst_flags_t complain)
{
  int ix, len = DECL_NTPARMS (tmpl);
  bool result = false;

  for (ix = 0; ix != len; ix++)
    {
      tree t = TREE_VEC_ELT (args, ix);

      if (TYPE_P (t))
	{
	  /* [basic.link]: A name with no linkage (notably, the name
	     of a class or enumeration declared in a local scope)
	     shall not be used to declare an entity with linkage.
	     This implies that names with no linkage cannot be used as
	     template arguments.  */
	  tree nt = no_linkage_check (t, /*relaxed_p=*/false);

	  if (nt)
	    {
	      /* DR 488 makes use of a type with no linkage cause
		 type deduction to fail.  */
	      if (complain & tf_error)
		{
		  if (TYPE_ANONYMOUS_P (nt))
		    error ("%qT is/uses anonymous type", t);
		  else
		    error ("template argument for %qD uses local type %qT",
			   tmpl, t);
		}
	      result = true;
	    }
	  /* In order to avoid all sorts of complications, we do not
	     allow variably-modified types as template arguments.  */
	  else if (variably_modified_type_p (t, NULL_TREE))
	    {
	      if (complain & tf_error)
		error ("%qT is a variably modified type", t);
	      result = true;
	    }
	}
      /* A non-type argument of integral or enumerated type must be a
	 constant.  */
      else if (TREE_TYPE (t)
	       && INTEGRAL_OR_ENUMERATION_TYPE_P (TREE_TYPE (t))
	       && !TREE_CONSTANT (t))
	{
	  if (complain & tf_error)
	    error ("integral expression %qE is not constant", t);
	  result = true;
	}
    }
  if (result && (complain & tf_error))
    error ("  trying to instantiate %qD", tmpl);
  return result;
}