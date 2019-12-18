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
 int /*<<< orphan*/  DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_EXPLICIT_INSTANTIATION (scalar_t__) ; 
 int /*<<< orphan*/  DECL_IMPLICIT_INSTANTIATION (scalar_t__) ; 
 int /*<<< orphan*/  DECL_LANG_SPECIFIC (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_NOT_REALLY_EXTERN (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_SPECIALIZATION (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ RID_EXTERN ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  check_explicit_instantiation_namespace (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  in_system_header ; 
 int /*<<< orphan*/  instantiate_decl (scalar_t__,int,int) ; 
 scalar_t__ lookup_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_decl_instantiated (scalar_t__,int) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,...) ; 
 scalar_t__* ridpointers ; 

void
do_decl_instantiation (tree decl, tree storage)
{
  tree result = NULL_TREE;
  int extern_p = 0;

  if (!decl || decl == error_mark_node)
    /* An error occurred, for which grokdeclarator has already issued
       an appropriate message.  */
    return;
  else if (! DECL_LANG_SPECIFIC (decl))
    {
      error ("explicit instantiation of non-template %q#D", decl);
      return;
    }
  else if (TREE_CODE (decl) == VAR_DECL)
    {
      /* There is an asymmetry here in the way VAR_DECLs and
	 FUNCTION_DECLs are handled by grokdeclarator.  In the case of
	 the latter, the DECL we get back will be marked as a
	 template instantiation, and the appropriate
	 DECL_TEMPLATE_INFO will be set up.  This does not happen for
	 VAR_DECLs so we do the lookup here.  Probably, grokdeclarator
	 should handle VAR_DECLs as it currently handles
	 FUNCTION_DECLs.  */
      result = lookup_field (DECL_CONTEXT (decl), DECL_NAME (decl), 0, false);
      if (!result || TREE_CODE (result) != VAR_DECL)
	{
	  error ("no matching template for %qD found", decl);
	  return;
	}
    }
  else if (TREE_CODE (decl) != FUNCTION_DECL)
    {
      error ("explicit instantiation of %q#D", decl);
      return;
    }
  else
    result = decl;

  /* Check for various error cases.  Note that if the explicit
     instantiation is valid the RESULT will currently be marked as an
     *implicit* instantiation; DECL_EXPLICIT_INSTANTIATION is not set
     until we get here.  */

  if (DECL_TEMPLATE_SPECIALIZATION (result))
    {
      /* DR 259 [temp.spec].

	 Both an explicit instantiation and a declaration of an explicit
	 specialization shall not appear in a program unless the explicit
	 instantiation follows a declaration of the explicit specialization.

	 For a given set of template parameters, if an explicit
	 instantiation of a template appears after a declaration of an
	 explicit specialization for that template, the explicit
	 instantiation has no effect.  */
      return;
    }
  else if (DECL_EXPLICIT_INSTANTIATION (result))
    {
      /* [temp.spec]

	 No program shall explicitly instantiate any template more
	 than once.

	 We check DECL_NOT_REALLY_EXTERN so as not to complain when
	 the first instantiation was `extern' and the second is not,
	 and EXTERN_P for the opposite case.  */
      if (DECL_NOT_REALLY_EXTERN (result) && !extern_p)
	pedwarn ("duplicate explicit instantiation of %q#D", result);
      /* If an "extern" explicit instantiation follows an ordinary
	 explicit instantiation, the template is instantiated.  */
      if (extern_p)
	return;
    }
  else if (!DECL_IMPLICIT_INSTANTIATION (result))
    {
      error ("no matching template for %qD found", result);
      return;
    }
  else if (!DECL_TEMPLATE_INFO (result))
    {
      pedwarn ("explicit instantiation of non-template %q#D", result);
      return;
    }

  if (storage == NULL_TREE)
    ;
  else if (storage == ridpointers[(int) RID_EXTERN])
    {
      if (pedantic && !in_system_header)
	pedwarn ("ISO C++ forbids the use of %<extern%> on explicit "
		 "instantiations");
      extern_p = 1;
    }
  else
    error ("storage class %qD applied to template instantiation", storage);

  check_explicit_instantiation_namespace (result);
  mark_decl_instantiated (result, extern_p);
  if (! extern_p)
    instantiate_decl (result, /*defer_ok=*/1,
		      /*expl_inst_class_mem_p=*/false);
}