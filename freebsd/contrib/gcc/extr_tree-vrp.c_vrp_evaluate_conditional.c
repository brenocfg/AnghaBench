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
typedef  int /*<<< orphan*/  location_t ;
typedef  enum warn_strict_overflow_code { ____Placeholder_warn_strict_overflow_code } warn_strict_overflow_code ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_HAS_LOCATION (scalar_t__) ; 
 int /*<<< orphan*/  EXPR_LOCATION (scalar_t__) ; 
 char* G_ (char*) ; 
 int /*<<< orphan*/  OPT_Wstrict_overflow ; 
 int WARN_STRICT_OVERFLOW_COMPARISON ; 
 int WARN_STRICT_OVERFLOW_CONDITIONAL ; 
 int /*<<< orphan*/  input_location ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 
 scalar_t__ issue_strict_overflow_warning (int) ; 
 scalar_t__ vrp_evaluate_conditional_warnv (scalar_t__,int,int*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*) ; 

tree
vrp_evaluate_conditional (tree cond, tree stmt)
{
  bool sop;
  tree ret;

  sop = false;
  ret = vrp_evaluate_conditional_warnv (cond, true, &sop);

  if (ret && sop)
    {
      enum warn_strict_overflow_code wc;
      const char* warnmsg;

      if (is_gimple_min_invariant (ret))
	{
	  wc = WARN_STRICT_OVERFLOW_CONDITIONAL;
	  warnmsg = G_("assuming signed overflow does not occur when "
		       "simplifying conditional to constant");
	}
      else
	{
	  wc = WARN_STRICT_OVERFLOW_COMPARISON;
	  warnmsg = G_("assuming signed overflow does not occur when "
		       "simplifying conditional");
	}

      if (issue_strict_overflow_warning (wc))
	{
	  location_t locus;

	  if (!EXPR_HAS_LOCATION (stmt))
	    locus = input_location;
	  else
	    locus = EXPR_LOCATION (stmt);
	  warning (OPT_Wstrict_overflow, "%H%s", &locus, warnmsg);
	}
    }

  return ret;
}