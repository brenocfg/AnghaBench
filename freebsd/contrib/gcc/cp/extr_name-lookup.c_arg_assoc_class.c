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
struct arg_lookup {scalar_t__ name; int /*<<< orphan*/  classes; } ;

/* Variables and functions */
 scalar_t__ BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 scalar_t__ CLASSTYPE_TEMPLATE_INFO (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_TEMPLATE (scalar_t__) ; 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ CP_DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_FRIENDLIST (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_USE_TEMPLATE (scalar_t__) ; 
 scalar_t__ FRIEND_DECLS (scalar_t__) ; 
 scalar_t__ FRIEND_NAME (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ INNERMOST_TEMPLATE_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ PRIMARY_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_DECL (scalar_t__) ; 
 scalar_t__ add_function (struct arg_lookup*,scalar_t__) ; 
 scalar_t__ arg_assoc_namespace (struct arg_lookup*,scalar_t__) ; 
 int /*<<< orphan*/  arg_assoc_template_arg (struct arg_lookup*,int /*<<< orphan*/ ) ; 
 scalar_t__ decl_namespace_context (scalar_t__) ; 
 scalar_t__ purpose_member (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
arg_assoc_class (struct arg_lookup *k, tree type)
{
  tree list, friends, context;
  int i;

  /* Backend build structures, such as __builtin_va_list, aren't
     affected by all this.  */
  if (!CLASS_TYPE_P (type))
    return false;

  if (purpose_member (type, k->classes))
    return false;
  k->classes = tree_cons (type, NULL_TREE, k->classes);

  context = decl_namespace_context (type);
  if (arg_assoc_namespace (k, context))
    return true;

  if (TYPE_BINFO (type))
    {
      /* Process baseclasses.  */
      tree binfo, base_binfo;

      for (binfo = TYPE_BINFO (type), i = 0;
	   BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
	if (arg_assoc_class (k, BINFO_TYPE (base_binfo)))
	  return true;
    }

  /* Process friends.  */
  for (list = DECL_FRIENDLIST (TYPE_MAIN_DECL (type)); list;
       list = TREE_CHAIN (list))
    if (k->name == FRIEND_NAME (list))
      for (friends = FRIEND_DECLS (list); friends;
	   friends = TREE_CHAIN (friends))
	{
	  tree fn = TREE_VALUE (friends);

	  /* Only interested in global functions with potentially hidden
	     (i.e. unqualified) declarations.  */
	  if (CP_DECL_CONTEXT (fn) != context)
	    continue;
	  /* Template specializations are never found by name lookup.
	     (Templates themselves can be found, but not template
	     specializations.)  */
	  if (TREE_CODE (fn) == FUNCTION_DECL && DECL_USE_TEMPLATE (fn))
	    continue;
	  if (add_function (k, fn))
	    return true;
	}

  /* Process template arguments.  */
  if (CLASSTYPE_TEMPLATE_INFO (type)
      && PRIMARY_TEMPLATE_P (CLASSTYPE_TI_TEMPLATE (type)))
    {
      list = INNERMOST_TEMPLATE_ARGS (CLASSTYPE_TI_ARGS (type));
      for (i = 0; i < TREE_VEC_LENGTH (list); ++i)
	arg_assoc_template_arg (k, TREE_VEC_ELT (list, i));
    }

  return false;
}