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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/ * CP_DECL_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DECL_CONTEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ DECL_NAMESPACE_STD_P (int /*<<< orphan*/ *) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_ARGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_TEMPLATE (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_CONTEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/ * TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TYPE_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ decl_is_template_id (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * global_namespace ; 
 int /*<<< orphan*/  write_local_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_nested_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_template_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unscoped_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unscoped_template_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_name (tree decl, const int ignore_local_scope)
{
  tree context;

  MANGLE_TRACE_TREE ("name", decl);

  if (TREE_CODE (decl) == TYPE_DECL)
    {
      /* In case this is a typedef, fish out the corresponding
	 TYPE_DECL for the main variant.  */
      decl = TYPE_NAME (TYPE_MAIN_VARIANT (TREE_TYPE (decl)));
      context = TYPE_CONTEXT (TYPE_MAIN_VARIANT (TREE_TYPE (decl)));
    }
  else
    context = (DECL_CONTEXT (decl) == NULL) ? NULL : CP_DECL_CONTEXT (decl);

  /* A decl in :: or ::std scope is treated specially.  The former is
     mangled using <unscoped-name> or <unscoped-template-name>, the
     latter with a special substitution.  Also, a name that is
     directly in a local function scope is also mangled with
     <unscoped-name> rather than a full <nested-name>.  */
  if (context == NULL
      || context == global_namespace
      || DECL_NAMESPACE_STD_P (context)
      || (ignore_local_scope && TREE_CODE (context) == FUNCTION_DECL))
    {
      tree template_info;
      /* Is this a template instance?  */
      if (decl_is_template_id (decl, &template_info))
	{
	  /* Yes: use <unscoped-template-name>.  */
	  write_unscoped_template_name (TI_TEMPLATE (template_info));
	  write_template_args (TI_ARGS (template_info));
	}
      else
	/* Everything else gets an <unqualified-name>.  */
	write_unscoped_name (decl);
    }
  else
    {
      /* Handle local names, unless we asked not to (that is, invoked
	 under <local-name>, to handle only the part of the name under
	 the local scope).  */
      if (!ignore_local_scope)
	{
	  /* Scan up the list of scope context, looking for a
	     function.  If we find one, this entity is in local
	     function scope.  local_entity tracks context one scope
	     level down, so it will contain the element that's
	     directly in that function's scope, either decl or one of
	     its enclosing scopes.  */
	  tree local_entity = decl;
	  while (context != NULL && context != global_namespace)
	    {
	      /* Make sure we're always dealing with decls.  */
	      if (context != NULL && TYPE_P (context))
		context = TYPE_NAME (context);
	      /* Is this a function?  */
	      if (TREE_CODE (context) == FUNCTION_DECL)
		{
		  /* Yes, we have local scope.  Use the <local-name>
		     production for the innermost function scope.  */
		  write_local_name (context, local_entity, decl);
		  return;
		}
	      /* Up one scope level.  */
	      local_entity = context;
	      context = CP_DECL_CONTEXT (context);
	    }

	  /* No local scope found?  Fall through to <nested-name>.  */
	}

      /* Other decls get a <nested-name> to encode their scope.  */
      write_nested_name (decl);
    }
}