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
 scalar_t__ DECL_CONST_MEMFUNC_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_FUNCTION_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_VOLATILE_MEMFUNC_P (int /*<<< orphan*/  const) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TI_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/  const) ; 
 scalar_t__ decl_is_template_id (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_template_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_template_prefix (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_unqualified_name (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
write_nested_name (const tree decl)
{
  tree template_info;

  MANGLE_TRACE_TREE ("nested-name", decl);

  write_char ('N');

  /* Write CV-qualifiers, if this is a member function.  */
  if (TREE_CODE (decl) == FUNCTION_DECL
      && DECL_NONSTATIC_MEMBER_FUNCTION_P (decl))
    {
      if (DECL_VOLATILE_MEMFUNC_P (decl))
	write_char ('V');
      if (DECL_CONST_MEMFUNC_P (decl))
	write_char ('K');
    }

  /* Is this a template instance?  */
  if (decl_is_template_id (decl, &template_info))
    {
      /* Yes, use <template-prefix>.  */
      write_template_prefix (decl);
      write_template_args (TI_ARGS (template_info));
    }
  else
    {
      /* No, just use <prefix>  */
      write_prefix (DECL_CONTEXT (decl));
      write_unqualified_name (decl);
    }
  write_char ('E');
}