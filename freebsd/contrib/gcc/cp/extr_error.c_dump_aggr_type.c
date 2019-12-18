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
 scalar_t__ ANON_AGGRNAME_P (scalar_t__) ; 
 scalar_t__ CLASSTYPE_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ CLASSTYPE_TI_TEMPLATE (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_USE_TEMPLATE (scalar_t__) ; 
 int /*<<< orphan*/  CP_DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_ARTIFICIAL (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ DECL_TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ ENUMERAL_TYPE ; 
 scalar_t__ PRIMARY_TEMPLATE_P (scalar_t__) ; 
 scalar_t__ TEMPLATE_DECL ; 
 int TFF_CHASE_TYPEDEF ; 
 int TFF_CLASS_KEY_OR_ENUM ; 
 int TFF_SCOPE ; 
 int TFF_TEMPLATE_HEADER ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_LANG_SPECIFIC (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_TEMPLATE_INFO (scalar_t__) ; 
 char* class_key_or_enum_as_string (scalar_t__) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_scope (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_template_parms (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pp_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pp_cxx_tree_identifier (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void
dump_aggr_type (tree t, int flags)
{
  tree name;
  const char *variety = class_key_or_enum_as_string (t);
  int typdef = 0;
  int tmplate = 0;

  pp_cxx_cv_qualifier_seq (cxx_pp, t);

  if (flags & TFF_CLASS_KEY_OR_ENUM)
    pp_cxx_identifier (cxx_pp, variety);

  if (flags & TFF_CHASE_TYPEDEF)
    t = TYPE_MAIN_VARIANT (t);

  name = TYPE_NAME (t);

  if (name)
    {
      typdef = !DECL_ARTIFICIAL (name);
      tmplate = !typdef && TREE_CODE (t) != ENUMERAL_TYPE
		&& TYPE_LANG_SPECIFIC (t) && CLASSTYPE_TEMPLATE_INFO (t)
		&& (TREE_CODE (CLASSTYPE_TI_TEMPLATE (t)) != TEMPLATE_DECL
		    || PRIMARY_TEMPLATE_P (CLASSTYPE_TI_TEMPLATE (t)));
      dump_scope (CP_DECL_CONTEXT (name), flags | TFF_SCOPE);
      if (tmplate)
	{
	  /* Because the template names are mangled, we have to locate
	     the most general template, and use that name.  */
	  tree tpl = CLASSTYPE_TI_TEMPLATE (t);

	  while (DECL_TEMPLATE_INFO (tpl))
	    tpl = DECL_TI_TEMPLATE (tpl);
	  name = tpl;
	}
      name = DECL_NAME (name);
    }

  if (name == 0 || ANON_AGGRNAME_P (name))
    {
      if (flags & TFF_CLASS_KEY_OR_ENUM)
	pp_identifier (cxx_pp, "<anonymous>");
      else
	pp_printf (pp_base (cxx_pp), "<anonymous %s>", variety);
    }
  else
    pp_cxx_tree_identifier (cxx_pp, name);
  if (tmplate)
    dump_template_parms (TYPE_TEMPLATE_INFO (t),
			 !CLASSTYPE_USE_TEMPLATE (t),
			 flags & ~TFF_TEMPLATE_HEADER);
}