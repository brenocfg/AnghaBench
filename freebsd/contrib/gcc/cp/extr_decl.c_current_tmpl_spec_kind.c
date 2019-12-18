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
typedef  int /*<<< orphan*/  tmpl_spec_kind ;
struct cp_binding_level {scalar_t__ kind; scalar_t__ explicit_spec_p; struct cp_binding_level* level_chain; } ;

/* Variables and functions */
 struct cp_binding_level* current_binding_level ; 
 scalar_t__ processing_explicit_instantiation ; 
 scalar_t__ sk_template_parms ; 
 int /*<<< orphan*/  tsk_excessive_parms ; 
 int /*<<< orphan*/  tsk_expl_inst ; 
 int /*<<< orphan*/  tsk_expl_spec ; 
 int /*<<< orphan*/  tsk_insufficient_parms ; 
 int /*<<< orphan*/  tsk_invalid_expl_inst ; 
 int /*<<< orphan*/  tsk_invalid_member_spec ; 
 int /*<<< orphan*/  tsk_none ; 
 int /*<<< orphan*/  tsk_template ; 

tmpl_spec_kind
current_tmpl_spec_kind (int n_class_scopes)
{
  int n_template_parm_scopes = 0;
  int seen_specialization_p = 0;
  int innermost_specialization_p = 0;
  struct cp_binding_level *b;

  /* Scan through the template parameter scopes.  */
  for (b = current_binding_level;
       b->kind == sk_template_parms;
       b = b->level_chain)
    {
      /* If we see a specialization scope inside a parameter scope,
	 then something is wrong.  That corresponds to a declaration
	 like:

	    template <class T> template <> ...

	 which is always invalid since [temp.expl.spec] forbids the
	 specialization of a class member template if the enclosing
	 class templates are not explicitly specialized as well.  */
      if (b->explicit_spec_p)
	{
	  if (n_template_parm_scopes == 0)
	    innermost_specialization_p = 1;
	  else
	    seen_specialization_p = 1;
	}
      else if (seen_specialization_p == 1)
	return tsk_invalid_member_spec;

      ++n_template_parm_scopes;
    }

  /* Handle explicit instantiations.  */
  if (processing_explicit_instantiation)
    {
      if (n_template_parm_scopes != 0)
	/* We've seen a template parameter list during an explicit
	   instantiation.  For example:

	     template <class T> template void f(int);

	   This is erroneous.  */
	return tsk_invalid_expl_inst;
      else
	return tsk_expl_inst;
    }

  if (n_template_parm_scopes < n_class_scopes)
    /* We've not seen enough template headers to match all the
       specialized classes present.  For example:

	 template <class T> void R<T>::S<T>::f(int);

       This is invalid; there needs to be one set of template
       parameters for each class.  */
    return tsk_insufficient_parms;
  else if (n_template_parm_scopes == n_class_scopes)
    /* We're processing a non-template declaration (even though it may
       be a member of a template class.)  For example:

	 template <class T> void S<T>::f(int);

       The `class T' maches the `S<T>', leaving no template headers
       corresponding to the `f'.  */
    return tsk_none;
  else if (n_template_parm_scopes > n_class_scopes + 1)
    /* We've got too many template headers.  For example:

	 template <> template <class T> void f (T);

       There need to be more enclosing classes.  */
    return tsk_excessive_parms;
  else
    /* This must be a template.  It's of the form:

	 template <class T> template <class U> void S<T>::f(U);

       This is a specialization if the innermost level was a
       specialization; otherwise it's just a definition of the
       template.  */
    return innermost_specialization_p ? tsk_expl_spec : tsk_template;
}