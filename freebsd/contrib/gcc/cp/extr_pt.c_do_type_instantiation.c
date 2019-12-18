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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ CLASSTYPE_EXPLICIT_INSTANTIATION (scalar_t__) ; 
 int CLASSTYPE_INTERFACE_ONLY (scalar_t__) ; 
 scalar_t__ CLASSTYPE_NESTED_UTDS (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ CLASSTYPE_TEMPLATE_SPECIALIZATION (scalar_t__) ; 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  COMPLETE_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_INSTANTIATION (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ RID_EXTERN ; 
 scalar_t__ RID_INLINE ; 
 scalar_t__ RID_STATIC ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_METHODS (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_NAME (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  binding_table_foreach (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  bt_instantiate_type_proc ; 
 int /*<<< orphan*/  check_explicit_instantiation_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_type (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  in_system_header ; 
 int /*<<< orphan*/  instantiate_class_member (scalar_t__,int) ; 
 int /*<<< orphan*/  mark_class_instantiated (scalar_t__,int) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,scalar_t__) ; 
 scalar_t__* ridpointers ; 
 int tf_error ; 

void
do_type_instantiation (tree t, tree storage, tsubst_flags_t complain)
{
  int extern_p = 0;
  int nomem_p = 0;
  int static_p = 0;
  int previous_instantiation_extern_p = 0;

  if (TREE_CODE (t) == TYPE_DECL)
    t = TREE_TYPE (t);

  if (! CLASS_TYPE_P (t) || ! CLASSTYPE_TEMPLATE_INFO (t))
    {
      error ("explicit instantiation of non-template type %qT", t);
      return;
    }

  complete_type (t);

  if (!COMPLETE_TYPE_P (t))
    {
      if (complain & tf_error)
	error ("explicit instantiation of %q#T before definition of template",
	       t);
      return;
    }

  if (storage != NULL_TREE)
    {
      if (pedantic && !in_system_header)
	pedwarn("ISO C++ forbids the use of %qE on explicit instantiations",
		storage);

      if (storage == ridpointers[(int) RID_INLINE])
	nomem_p = 1;
      else if (storage == ridpointers[(int) RID_EXTERN])
	extern_p = 1;
      else if (storage == ridpointers[(int) RID_STATIC])
	static_p = 1;
      else
	{
	  error ("storage class %qD applied to template instantiation",
		 storage);
	  extern_p = 0;
	}
    }

  if (CLASSTYPE_TEMPLATE_SPECIALIZATION (t))
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
  else if (CLASSTYPE_EXPLICIT_INSTANTIATION (t))
    {
      /* [temp.spec]

	 No program shall explicitly instantiate any template more
	 than once.

	 If PREVIOUS_INSTANTIATION_EXTERN_P, then the first explicit
	 instantiation was `extern'.  If EXTERN_P then the second is.
	 These cases are OK.  */
      previous_instantiation_extern_p = CLASSTYPE_INTERFACE_ONLY (t);

      if (!previous_instantiation_extern_p && !extern_p
	  && (complain & tf_error))
	pedwarn ("duplicate explicit instantiation of %q#T", t);

      /* If we've already instantiated the template, just return now.  */
      if (!CLASSTYPE_INTERFACE_ONLY (t))
	return;
    }

  check_explicit_instantiation_namespace (TYPE_NAME (t));
  mark_class_instantiated (t, extern_p);

  if (nomem_p)
    return;

  {
    tree tmp;

    /* In contrast to implicit instantiation, where only the
       declarations, and not the definitions, of members are
       instantiated, we have here:

	 [temp.explicit]

	 The explicit instantiation of a class template specialization
	 implies the instantiation of all of its members not
	 previously explicitly specialized in the translation unit
	 containing the explicit instantiation.

       Of course, we can't instantiate member template classes, since
       we don't have any arguments for them.  Note that the standard
       is unclear on whether the instantiation of the members are
       *explicit* instantiations or not.  However, the most natural
       interpretation is that it should be an explicit instantiation.  */

    if (! static_p)
      for (tmp = TYPE_METHODS (t); tmp; tmp = TREE_CHAIN (tmp))
	if (TREE_CODE (tmp) == FUNCTION_DECL
	    && DECL_TEMPLATE_INSTANTIATION (tmp))
	  instantiate_class_member (tmp, extern_p);

    for (tmp = TYPE_FIELDS (t); tmp; tmp = TREE_CHAIN (tmp))
      if (TREE_CODE (tmp) == VAR_DECL && DECL_TEMPLATE_INSTANTIATION (tmp))
	instantiate_class_member (tmp, extern_p);

    if (CLASSTYPE_NESTED_UTDS (t))
      binding_table_foreach (CLASSTYPE_NESTED_UTDS (t),
			     bt_instantiate_type_proc, &storage);
  }
}