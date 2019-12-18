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
 int /*<<< orphan*/  CLASSTYPE_TEMPLATE_SPECIALIZATION (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CLASS_SCOPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CONV_FN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FRIEND_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_FUNCTION_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_MEMBER_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_RESULT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
optimize_specialization_lookup_p (tree tmpl)
{
  return (DECL_FUNCTION_TEMPLATE_P (tmpl)
	  && DECL_CLASS_SCOPE_P (tmpl)
	  /* DECL_CLASS_SCOPE_P holds of T::f even if T is a template
	     parameter.  */
	  && CLASS_TYPE_P (DECL_CONTEXT (tmpl))
	  /* The optimized lookup depends on the fact that the
	     template arguments for the member function template apply
	     purely to the containing class, which is not true if the
	     containing class is an explicit or partial
	     specialization.  */
	  && !CLASSTYPE_TEMPLATE_SPECIALIZATION (DECL_CONTEXT (tmpl))
	  && !DECL_MEMBER_TEMPLATE_P (tmpl)
	  && !DECL_CONV_FN_P (tmpl)
	  /* It is possible to have a template that is not a member
	     template and is not a member of a template class:

	     template <typename T>
	     struct S { friend A::f(); };

	     Here, the friend function is a template, but the context does
	     not have template information.  The optimized lookup relies
	     on having ARGS be the template arguments for both the class
	     and the function template.  */
	  && !DECL_FRIEND_P (DECL_TEMPLATE_RESULT (tmpl)));
}