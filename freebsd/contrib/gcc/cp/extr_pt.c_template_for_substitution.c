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
 scalar_t__ DECL_FRIEND_PSEUDO_TEMPLATE_INSTANTIATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_IN_AGGR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_TEMPLATE_INSTANTIATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TI_TEMPLATE (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
template_for_substitution (tree decl)
{
  tree tmpl = DECL_TI_TEMPLATE (decl);

  /* Set TMPL to the template whose DECL_TEMPLATE_RESULT is the pattern
     for the instantiation.  This is not always the most general
     template.  Consider, for example:

	template <class T>
	struct S { template <class U> void f();
		   template <> void f<int>(); };

     and an instantiation of S<double>::f<int>.  We want TD to be the
     specialization S<T>::f<int>, not the more general S<T>::f<U>.  */
  while (/* An instantiation cannot have a definition, so we need a
	    more general template.  */
	 DECL_TEMPLATE_INSTANTIATION (tmpl)
	   /* We must also deal with friend templates.  Given:

		template <class T> struct S {
		  template <class U> friend void f() {};
		};

	      S<int>::f<U> say, is not an instantiation of S<T>::f<U>,
	      so far as the language is concerned, but that's still
	      where we get the pattern for the instantiation from.  On
	      other hand, if the definition comes outside the class, say:

		template <class T> struct S {
		  template <class U> friend void f();
		};
		template <class U> friend void f() {}

	      we don't need to look any further.  That's what the check for
	      DECL_INITIAL is for.  */
	  || (TREE_CODE (decl) == FUNCTION_DECL
	      && DECL_FRIEND_PSEUDO_TEMPLATE_INSTANTIATION (tmpl)
	      && !DECL_INITIAL (DECL_TEMPLATE_RESULT (tmpl))))
    {
      /* The present template, TD, should not be a definition.  If it
	 were a definition, we should be using it!  Note that we
	 cannot restructure the loop to just keep going until we find
	 a template with a definition, since that might go too far if
	 a specialization was declared, but not defined.  */
      gcc_assert (TREE_CODE (decl) != VAR_DECL
		  || DECL_IN_AGGR_P (DECL_TEMPLATE_RESULT (tmpl)));

      /* Fetch the more general template.  */
      tmpl = DECL_TI_TEMPLATE (tmpl);
    }

  return tmpl;
}