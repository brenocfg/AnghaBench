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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_LANG_SPECIFIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAMESPACE_ALIAS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SAVED_TREE (int /*<<< orphan*/ ) ; 
 int DECL_USE_TEMPLATE (int /*<<< orphan*/ ) ; 
#define  FUNCTION_DECL 131 
#define  NAMESPACE_DECL 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 129 
#define  VAR_DECL 128 
 int /*<<< orphan*/  pp_cxx_explicit_instantiation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_explicit_specialization (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_function_definition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_namespace_alias_definition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_original_namespace_definition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_simple_declaration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_template_declaration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_cxx_declaration (cxx_pretty_printer *pp, tree t)
{
  if (!DECL_LANG_SPECIFIC (t))
    pp_cxx_simple_declaration (pp, t);
  else if (DECL_USE_TEMPLATE (t))
    switch (DECL_USE_TEMPLATE (t))
      {
      case 1:
	pp_cxx_template_declaration (pp, t);
	break;

      case 2:
	pp_cxx_explicit_specialization (pp, t);
	break;

      case 3:
	pp_cxx_explicit_instantiation (pp, t);
	break;

      default:
	break;
      }
  else switch (TREE_CODE (t))
    {
    case VAR_DECL:
    case TYPE_DECL:
      pp_cxx_simple_declaration (pp, t);
      break;

    case FUNCTION_DECL:
      if (DECL_SAVED_TREE (t))
	pp_cxx_function_definition (pp, t);
      else
	pp_cxx_simple_declaration (pp, t);
      break;

    case NAMESPACE_DECL:
      if (DECL_NAMESPACE_ALIAS (t))
	pp_cxx_namespace_alias_definition (pp, t);
      else
	pp_cxx_original_namespace_definition (pp, t);
      break;

    default:
      pp_unsupported_tree (pp, t);
      break;
    }
}