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
struct arg_lookup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ UNBOUND_CLASS_TEMPLATE ; 
 int arg_assoc_class (struct arg_lookup*,int /*<<< orphan*/ ) ; 
 int arg_assoc_namespace (struct arg_lookup*,int /*<<< orphan*/ ) ; 
 int arg_assoc_type (struct arg_lookup*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
arg_assoc_template_arg (struct arg_lookup *k, tree arg)
{
  /* [basic.lookup.koenig]

     If T is a template-id, its associated namespaces and classes are
     ... the namespaces and classes associated with the types of the
     template arguments provided for template type parameters
     (excluding template template parameters); the namespaces in which
     any template template arguments are defined; and the classes in
     which any member templates used as template template arguments
     are defined.  [Note: non-type template arguments do not
     contribute to the set of associated namespaces.  ]  */

  /* Consider first template template arguments.  */
  if (TREE_CODE (arg) == TEMPLATE_TEMPLATE_PARM
      || TREE_CODE (arg) == UNBOUND_CLASS_TEMPLATE)
    return false;
  else if (TREE_CODE (arg) == TEMPLATE_DECL)
    {
      tree ctx = CP_DECL_CONTEXT (arg);

      /* It's not a member template.  */
      if (TREE_CODE (ctx) == NAMESPACE_DECL)
	return arg_assoc_namespace (k, ctx);
      /* Otherwise, it must be member template.  */
      else
	return arg_assoc_class (k, ctx);
    }
  /* It's not a template template argument, but it is a type template
     argument.  */
  else if (TYPE_P (arg))
    return arg_assoc_type (k, arg);
  /* It's a non-type template argument.  */
  else
    return false;
}