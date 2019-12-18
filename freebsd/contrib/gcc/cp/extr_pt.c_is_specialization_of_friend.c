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
 scalar_t__ CLASSTYPE_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ CLASSTYPE_TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ DECL_CLASS_SCOPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_FUNCTION_P (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_INFO (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_PARMS (scalar_t__) ; 
 scalar_t__ DECL_TI_TEMPLATE (scalar_t__) ; 
 int /*<<< orphan*/  DECL_USE_TEMPLATE (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PRIMARY_TEMPLATE_P (scalar_t__) ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 scalar_t__ TYPE_TI_ARGS (scalar_t__) ; 
 scalar_t__ add_to_template_args (scalar_t__,scalar_t__) ; 
 int comp_template_parms (int /*<<< orphan*/ ,scalar_t__) ; 
 int compparms (scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ is_specialization_of (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  same_type_p (scalar_t__,scalar_t__) ; 
 int template_class_depth (scalar_t__) ; 
 int /*<<< orphan*/  tf_none ; 
 scalar_t__ tsubst_function_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tsubst_template_parms (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

bool
is_specialization_of_friend (tree decl, tree friend)
{
  bool need_template = true;
  int template_depth;

  gcc_assert (TREE_CODE (decl) == FUNCTION_DECL
	      || TREE_CODE (decl) == TYPE_DECL);

  /* For [temp.friend/6] when FRIEND is an ordinary member function
     of a template class, we want to check if DECL is a specialization
     if this.  */
  if (TREE_CODE (friend) == FUNCTION_DECL
      && DECL_TEMPLATE_INFO (friend)
      && !DECL_USE_TEMPLATE (friend))
    {
      /* We want a TEMPLATE_DECL for `is_specialization_of'.  */
      friend = DECL_TI_TEMPLATE (friend);
      need_template = false;
    }
  else if (TREE_CODE (friend) == TEMPLATE_DECL
	   && !PRIMARY_TEMPLATE_P (friend))
    need_template = false;

  /* There is nothing to do if this is not a template friend.  */
  if (TREE_CODE (friend) != TEMPLATE_DECL)
    return false;

  if (is_specialization_of (decl, friend))
    return true;

  /* [temp.friend/6]
     A member of a class template may be declared to be a friend of a
     non-template class.  In this case, the corresponding member of
     every specialization of the class template is a friend of the
     class granting friendship.

     For example, given a template friend declaration

       template <class T> friend void A<T>::f();

     the member function below is considered a friend

       template <> struct A<int> {
	 void f();
       };

     For this type of template friend, TEMPLATE_DEPTH below will be
     nonzero.  To determine if DECL is a friend of FRIEND, we first
     check if the enclosing class is a specialization of another.  */

  template_depth = template_class_depth (DECL_CONTEXT (friend));
  if (template_depth
      && DECL_CLASS_SCOPE_P (decl)
      && is_specialization_of (TYPE_NAME (DECL_CONTEXT (decl)),
			       CLASSTYPE_TI_TEMPLATE (DECL_CONTEXT (friend))))
    {
      /* Next, we check the members themselves.  In order to handle
	 a few tricky cases, such as when FRIEND's are

	   template <class T> friend void A<T>::g(T t);
	   template <class T> template <T t> friend void A<T>::h();

	 and DECL's are

	   void A<int>::g(int);
	   template <int> void A<int>::h();

	 we need to figure out ARGS, the template arguments from
	 the context of DECL.  This is required for template substitution
	 of `T' in the function parameter of `g' and template parameter
	 of `h' in the above examples.  Here ARGS corresponds to `int'.  */

      tree context = DECL_CONTEXT (decl);
      tree args = NULL_TREE;
      int current_depth = 0;

      while (current_depth < template_depth)
	{
	  if (CLASSTYPE_TEMPLATE_INFO (context))
	    {
	      if (current_depth == 0)
		args = TYPE_TI_ARGS (context);
	      else
		args = add_to_template_args (TYPE_TI_ARGS (context), args);
	      current_depth++;
	    }
	  context = TYPE_CONTEXT (context);
	}

      if (TREE_CODE (decl) == FUNCTION_DECL)
	{
	  bool is_template;
	  tree friend_type;
	  tree decl_type;
	  tree friend_args_type;
	  tree decl_args_type;

	  /* Make sure that both DECL and FRIEND are templates or
	     non-templates.  */
	  is_template = DECL_TEMPLATE_INFO (decl)
			&& PRIMARY_TEMPLATE_P (DECL_TI_TEMPLATE (decl));
	  if (need_template ^ is_template)
	    return false;
	  else if (is_template)
	    {
	      /* If both are templates, check template parameter list.  */
	      tree friend_parms
		= tsubst_template_parms (DECL_TEMPLATE_PARMS (friend),
					 args, tf_none);
	      if (!comp_template_parms
		     (DECL_TEMPLATE_PARMS (DECL_TI_TEMPLATE (decl)),
		      friend_parms))
		return false;

	      decl_type = TREE_TYPE (DECL_TI_TEMPLATE (decl));
	    }
	  else
	    decl_type = TREE_TYPE (decl);

	  friend_type = tsubst_function_type (TREE_TYPE (friend), args,
					      tf_none, NULL_TREE);
	  if (friend_type == error_mark_node)
	    return false;

	  /* Check if return types match.  */
	  if (!same_type_p (TREE_TYPE (decl_type), TREE_TYPE (friend_type)))
	    return false;

	  /* Check if function parameter types match, ignoring the
	     `this' parameter.  */
	  friend_args_type = TYPE_ARG_TYPES (friend_type);
	  decl_args_type = TYPE_ARG_TYPES (decl_type);
	  if (DECL_NONSTATIC_MEMBER_FUNCTION_P (friend))
	    friend_args_type = TREE_CHAIN (friend_args_type);
	  if (DECL_NONSTATIC_MEMBER_FUNCTION_P (decl))
	    decl_args_type = TREE_CHAIN (decl_args_type);

	  return compparms (decl_args_type, friend_args_type);
	}
      else
	{
	  /* DECL is a TYPE_DECL */
	  bool is_template;
	  tree decl_type = TREE_TYPE (decl);

	  /* Make sure that both DECL and FRIEND are templates or
	     non-templates.  */
	  is_template
	    = CLASSTYPE_TEMPLATE_INFO (decl_type)
	      && PRIMARY_TEMPLATE_P (CLASSTYPE_TI_TEMPLATE (decl_type));

	  if (need_template ^ is_template)
	    return false;
	  else if (is_template)
	    {
	      tree friend_parms;
	      /* If both are templates, check the name of the two
		 TEMPLATE_DECL's first because is_friend didn't.  */
	      if (DECL_NAME (CLASSTYPE_TI_TEMPLATE (decl_type))
		  != DECL_NAME (friend))
		return false;

	      /* Now check template parameter list.  */
	      friend_parms
		= tsubst_template_parms (DECL_TEMPLATE_PARMS (friend),
					 args, tf_none);
	      return comp_template_parms
		(DECL_TEMPLATE_PARMS (CLASSTYPE_TI_TEMPLATE (decl_type)),
		 friend_parms);
	    }
	  else
	    return (DECL_NAME (decl)
		    == DECL_NAME (friend));
	}
    }
  return false;
}