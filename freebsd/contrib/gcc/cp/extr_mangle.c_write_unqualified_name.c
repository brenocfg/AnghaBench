#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/  mangled_name; } ;
typedef  TYPE_1__ operator_name_info_t ;

/* Variables and functions */
 scalar_t__ DECL_ASSEMBLER_NAME (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_ASSIGNMENT_OPERATOR_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_CONSTRUCTOR_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_CONV_FN_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_CONV_FN_TYPE (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_DESTRUCTOR_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * DECL_LANG_SPECIFIC (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_NAMESPACE_SCOPE_P (int /*<<< orphan*/  const) ; 
 size_t DECL_OVERLOADED_OPERATOR_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/  const) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_OR_FUNCTION_DECL_P (int /*<<< orphan*/  const) ; 
 TYPE_1__* assignment_operator_name_info ; 
 scalar_t__ decl_is_template_id (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 scalar_t__ decl_linkage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_mostly_instantiated_function_type (int /*<<< orphan*/  const) ; 
 scalar_t__ lk_internal ; 
 TYPE_1__* operator_name_info ; 
 int /*<<< orphan*/  restore_partially_mangled_name () ; 
 int /*<<< orphan*/  save_partially_mangled_name () ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_conversion_operator_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_source_name (scalar_t__) ; 
 int /*<<< orphan*/  write_special_name_constructor (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_special_name_destructor (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_unqualified_name (const tree decl)
{
  MANGLE_TRACE_TREE ("unqualified-name", decl);

  if (DECL_LANG_SPECIFIC (decl) != NULL && DECL_CONSTRUCTOR_P (decl))
    write_special_name_constructor (decl);
  else if (DECL_LANG_SPECIFIC (decl) != NULL && DECL_DESTRUCTOR_P (decl))
    write_special_name_destructor (decl);
  else if (DECL_NAME (decl) == NULL_TREE)
    write_source_name (DECL_ASSEMBLER_NAME (decl));
  else if (DECL_CONV_FN_P (decl))
    {
      /* Conversion operator. Handle it right here.
	   <operator> ::= cv <type>  */
      tree type;
      if (decl_is_template_id (decl, NULL))
	{
	  tree fn_type;
	  save_partially_mangled_name ();
	  fn_type = get_mostly_instantiated_function_type (decl);
	  restore_partially_mangled_name ();
	  type = TREE_TYPE (fn_type);
	}
      else
	type = DECL_CONV_FN_TYPE (decl);
      write_conversion_operator_name (type);
    }
  else if (DECL_OVERLOADED_OPERATOR_P (decl))
    {
      operator_name_info_t *oni;
      if (DECL_ASSIGNMENT_OPERATOR_P (decl))
	oni = assignment_operator_name_info;
      else
	oni = operator_name_info;

      write_string (oni[DECL_OVERLOADED_OPERATOR_P (decl)].mangled_name);
    }
  else if (VAR_OR_FUNCTION_DECL_P (decl) && ! TREE_PUBLIC (decl)
	   && DECL_NAMESPACE_SCOPE_P (decl)
	   && decl_linkage (decl) == lk_internal)
    {
      MANGLE_TRACE_TREE ("local-source-name", decl);
      write_char ('L');
      write_source_name (DECL_NAME (decl));
      /* The default discriminator is 1, and that's all we ever use,
	 so there's no code to output one here.  */
    }
  else
    write_source_name (DECL_NAME (decl));
}