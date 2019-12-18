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
 scalar_t__ DECL_TEMPLATE_PARMS (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int TFF_CLASS_KEY_OR_ENUM ; 
 int TFF_DECL_SPECIFIERS ; 
 int TFF_TEMPLATE_NAME ; 
 scalar_t__ TI_ARGS (scalar_t__) ; 
 scalar_t__ TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ TMPL_ARGS_HAVE_MULTIPLE_LEVELS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_LIST ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_decl (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_template_argument (scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  pp_cxx_begin_template_argument_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_end_template_argument_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_separate_with_comma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_template_parms (tree info, int primary, int flags)
{
  tree args = info ? TI_ARGS (info) : NULL_TREE;

  if (primary && flags & TFF_TEMPLATE_NAME)
    return;
  flags &= ~(TFF_CLASS_KEY_OR_ENUM | TFF_TEMPLATE_NAME);
  pp_cxx_begin_template_argument_list (cxx_pp);

  /* Be careful only to print things when we have them, so as not
	 to crash producing error messages.  */
  if (args && !primary)
    {
      int len, ix;

      if (TMPL_ARGS_HAVE_MULTIPLE_LEVELS (args))
	args = TREE_VEC_ELT (args, TREE_VEC_LENGTH (args) - 1);

      len = TREE_VEC_LENGTH (args);

      for (ix = 0; ix != len; ix++)
	{
	  tree arg = TREE_VEC_ELT (args, ix);

	  if (ix)
	    pp_separate_with_comma (cxx_pp);

	  if (!arg)
	    pp_identifier (cxx_pp, "<template parameter error>");
	  else
	    dump_template_argument (arg, flags);
	}
    }
  else if (primary)
    {
      tree tpl = TI_TEMPLATE (info);
      tree parms = DECL_TEMPLATE_PARMS (tpl);
      int len, ix;

      parms = TREE_CODE (parms) == TREE_LIST ? TREE_VALUE (parms) : NULL_TREE;
      len = parms ? TREE_VEC_LENGTH (parms) : 0;

      for (ix = 0; ix != len; ix++)
	{
	  tree parm;

          if (TREE_VEC_ELT (parms, ix) == error_mark_node)
            {
              pp_identifier (cxx_pp, "<template parameter error>");
              continue;
            }

          parm = TREE_VALUE (TREE_VEC_ELT (parms, ix));

	  if (ix)
	    pp_separate_with_comma (cxx_pp);

	  dump_decl (parm, flags & ~TFF_DECL_SPECIFIERS);
	}
    }
  pp_cxx_end_template_argument_list (cxx_pp);
}