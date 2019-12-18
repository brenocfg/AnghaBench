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
struct arg_lookup {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ BASELINK ; 
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ CP_DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ OFFSET_REF ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_CHAIN (scalar_t__) ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_FUNCTION (scalar_t__) ; 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_LIST ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int arg_assoc_class (struct arg_lookup*,scalar_t__) ; 
 int arg_assoc_namespace (struct arg_lookup*,scalar_t__) ; 
 int arg_assoc_template_arg (struct arg_lookup*,int /*<<< orphan*/ ) ; 
 int arg_assoc_type (struct arg_lookup*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  type_unknown_p (scalar_t__) ; 

__attribute__((used)) static bool
arg_assoc (struct arg_lookup *k, tree n)
{
  if (n == error_mark_node)
    return false;

  if (TYPE_P (n))
    return arg_assoc_type (k, n);

  if (! type_unknown_p (n))
    return arg_assoc_type (k, TREE_TYPE (n));

  if (TREE_CODE (n) == ADDR_EXPR)
    n = TREE_OPERAND (n, 0);
  if (TREE_CODE (n) == COMPONENT_REF)
    n = TREE_OPERAND (n, 1);
  if (TREE_CODE (n) == OFFSET_REF)
    n = TREE_OPERAND (n, 1);
  while (TREE_CODE (n) == TREE_LIST)
    n = TREE_VALUE (n);
  if (TREE_CODE (n) == BASELINK)
    n = BASELINK_FUNCTIONS (n);

  if (TREE_CODE (n) == FUNCTION_DECL)
    return arg_assoc_type (k, TREE_TYPE (n));
  if (TREE_CODE (n) == TEMPLATE_ID_EXPR)
    {
      /* [basic.lookup.koenig]

	 If T is a template-id, its associated namespaces and classes
	 are the namespace in which the template is defined; for
	 member templates, the member template's class...  */
      tree template = TREE_OPERAND (n, 0);
      tree args = TREE_OPERAND (n, 1);
      tree ctx;
      int ix;

      if (TREE_CODE (template) == COMPONENT_REF)
	template = TREE_OPERAND (template, 1);

      /* First, the template.  There may actually be more than one if
	 this is an overloaded function template.  But, in that case,
	 we only need the first; all the functions will be in the same
	 namespace.  */
      template = OVL_CURRENT (template);

      ctx = CP_DECL_CONTEXT (template);

      if (TREE_CODE (ctx) == NAMESPACE_DECL)
	{
	  if (arg_assoc_namespace (k, ctx) == 1)
	    return true;
	}
      /* It must be a member template.  */
      else if (arg_assoc_class (k, ctx) == 1)
	return true;

      /* Now the arguments.  */
      if (args)
	for (ix = TREE_VEC_LENGTH (args); ix--;)
	  if (arg_assoc_template_arg (k, TREE_VEC_ELT (args, ix)) == 1)
	    return true;
    }
  else if (TREE_CODE (n) == OVERLOAD)
    {
      for (; n; n = OVL_CHAIN (n))
	if (arg_assoc_type (k, TREE_TYPE (OVL_FUNCTION (n))))
	  return true;
    }

  return false;
}