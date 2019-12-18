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
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ BOUND_TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ CLASSTYPE_TEMPLATE_INFO (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (scalar_t__) ; 
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ FUNCTION_TYPE ; 
 int /*<<< orphan*/  INNERMOST_TEMPLATE_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPENAME_TYPE ; 
 scalar_t__ TYPEOF_TYPE ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 scalar_t__ TYPE_DOMAIN (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_CLASS_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_POINTED_TO_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTR_TO_MEMBER_P (scalar_t__) ; 
 scalar_t__ any_dependent_template_arguments_p (int /*<<< orphan*/ ) ; 
 int dependent_type_p (scalar_t__) ; 
 int type_dependent_expression_p (scalar_t__) ; 
 scalar_t__ value_dependent_expression_p (scalar_t__) ; 

__attribute__((used)) static bool
dependent_type_p_r (tree type)
{
  tree scope;

  /* [temp.dep.type]

     A type is dependent if it is:

     -- a template parameter. Template template parameters are types
	for us (since TYPE_P holds true for them) so we handle
	them here.  */
  if (TREE_CODE (type) == TEMPLATE_TYPE_PARM
      || TREE_CODE (type) == TEMPLATE_TEMPLATE_PARM)
    return true;
  /* -- a qualified-id with a nested-name-specifier which contains a
	class-name that names a dependent type or whose unqualified-id
	names a dependent type.  */
  if (TREE_CODE (type) == TYPENAME_TYPE)
    return true;
  /* -- a cv-qualified type where the cv-unqualified type is
	dependent.  */
  type = TYPE_MAIN_VARIANT (type);
  /* -- a compound type constructed from any dependent type.  */
  if (TYPE_PTR_TO_MEMBER_P (type))
    return (dependent_type_p (TYPE_PTRMEM_CLASS_TYPE (type))
	    || dependent_type_p (TYPE_PTRMEM_POINTED_TO_TYPE
					   (type)));
  else if (TREE_CODE (type) == POINTER_TYPE
	   || TREE_CODE (type) == REFERENCE_TYPE)
    return dependent_type_p (TREE_TYPE (type));
  else if (TREE_CODE (type) == FUNCTION_TYPE
	   || TREE_CODE (type) == METHOD_TYPE)
    {
      tree arg_type;

      if (dependent_type_p (TREE_TYPE (type)))
	return true;
      for (arg_type = TYPE_ARG_TYPES (type);
	   arg_type;
	   arg_type = TREE_CHAIN (arg_type))
	if (dependent_type_p (TREE_VALUE (arg_type)))
	  return true;
      return false;
    }
  /* -- an array type constructed from any dependent type or whose
	size is specified by a constant expression that is
	value-dependent.  */
  if (TREE_CODE (type) == ARRAY_TYPE)
    {
      if (TYPE_DOMAIN (type)
	  && ((value_dependent_expression_p
	       (TYPE_MAX_VALUE (TYPE_DOMAIN (type))))
	      || (type_dependent_expression_p
		  (TYPE_MAX_VALUE (TYPE_DOMAIN (type))))))
	return true;
      return dependent_type_p (TREE_TYPE (type));
    }

  /* -- a template-id in which either the template name is a template
     parameter ...  */
  if (TREE_CODE (type) == BOUND_TEMPLATE_TEMPLATE_PARM)
    return true;
  /* ... or any of the template arguments is a dependent type or
	an expression that is type-dependent or value-dependent.  */
  else if (CLASS_TYPE_P (type) && CLASSTYPE_TEMPLATE_INFO (type)
	   && (any_dependent_template_arguments_p
	       (INNERMOST_TEMPLATE_ARGS (CLASSTYPE_TI_ARGS (type)))))
    return true;

  /* All TYPEOF_TYPEs are dependent; if the argument of the `typeof'
     expression is not type-dependent, then it should already been
     have resolved.  */
  if (TREE_CODE (type) == TYPEOF_TYPE)
    return true;

  /* The standard does not specifically mention types that are local
     to template functions or local classes, but they should be
     considered dependent too.  For example:

       template <int I> void f() {
	 enum E { a = I };
	 S<sizeof (E)> s;
       }

     The size of `E' cannot be known until the value of `I' has been
     determined.  Therefore, `E' must be considered dependent.  */
  scope = TYPE_CONTEXT (type);
  if (scope && TYPE_P (scope))
    return dependent_type_p (scope);
  else if (scope && TREE_CODE (scope) == FUNCTION_DECL)
    return type_dependent_expression_p (scope);

  /* Other types are non-dependent.  */
  return false;
}