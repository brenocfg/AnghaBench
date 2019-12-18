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
 int /*<<< orphan*/  DECL_CONSTRUCTOR_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_CONV_FN_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_DESTRUCTOR_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_EXTERN_C_FUNCTION_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_LANG_SPECIFIC (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_OVERLOADED_OPERATOR_P (int /*<<< orphan*/  const) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/  const) ; 
 scalar_t__ decl_is_template_id (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mostly_instantiated_function_type (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  restore_partially_mangled_name () ; 
 int /*<<< orphan*/  save_partially_mangled_name () ; 
 int /*<<< orphan*/  write_bare_function_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_name (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_source_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_encoding (const tree decl)
{
  MANGLE_TRACE_TREE ("encoding", decl);

  if (DECL_LANG_SPECIFIC (decl) && DECL_EXTERN_C_FUNCTION_P (decl))
    {
      /* For overloaded operators write just the mangled name
	 without arguments.  */
      if (DECL_OVERLOADED_OPERATOR_P (decl))
	write_name (decl, /*ignore_local_scope=*/0);
      else
	write_source_name (DECL_NAME (decl));
      return;
    }

  write_name (decl, /*ignore_local_scope=*/0);
  if (TREE_CODE (decl) == FUNCTION_DECL)
    {
      tree fn_type;
      tree d;

      if (decl_is_template_id (decl, NULL))
	{
	  save_partially_mangled_name ();
	  fn_type = get_mostly_instantiated_function_type (decl);
	  restore_partially_mangled_name ();
	  /* FN_TYPE will not have parameter types for in-charge or
	     VTT parameters.  Therefore, we pass NULL_TREE to
	     write_bare_function_type -- otherwise, it will get
	     confused about which artificial parameters to skip.  */
	  d = NULL_TREE;
	}
      else
	{
	  fn_type = TREE_TYPE (decl);
	  d = decl;
	}

      write_bare_function_type (fn_type,
				(!DECL_CONSTRUCTOR_P (decl)
				 && !DECL_DESTRUCTOR_P (decl)
				 && !DECL_CONV_FN_P (decl)
				 && decl_is_template_id (decl, NULL)),
				d);
    }
}