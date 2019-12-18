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
typedef  scalar_t__ rtx ;
typedef  scalar_t__ regset ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARISON_P (scalar_t__) ; 
 int /*<<< orphan*/  altered_reg_used ; 
 scalar_t__ canon_condition (scalar_t__) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const_true_rtx ; 
 scalar_t__ for_each_rtx (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ implies_p (scalar_t__,scalar_t__) ; 
 scalar_t__ reversed_condition (scalar_t__) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

void
simplify_using_condition (rtx cond, rtx *expr, regset altered)
{
  rtx rev, reve, exp = *expr;

  if (!COMPARISON_P (exp))
    return;

  /* If some register gets altered later, we do not really speak about its
     value at the time of comparison.  */
  if (altered
      && for_each_rtx (&cond, altered_reg_used, altered))
    return;

  rev = reversed_condition (cond);
  reve = reversed_condition (exp);

  cond = canon_condition (cond);
  exp = canon_condition (exp);
  if (rev)
    rev = canon_condition (rev);
  if (reve)
    reve = canon_condition (reve);

  if (rtx_equal_p (exp, cond))
    {
      *expr = const_true_rtx;
      return;
    }


  if (rev && rtx_equal_p (exp, rev))
    {
      *expr = const0_rtx;
      return;
    }

  if (implies_p (cond, exp))
    {
      *expr = const_true_rtx;
      return;
    }
  
  if (reve && implies_p (cond, reve))
    {
      *expr = const0_rtx;
      return;
    }

  /* A proof by contradiction.  If *EXPR implies (not cond), *EXPR must
     be false.  */
  if (rev && implies_p (exp, rev))
    {
      *expr = const0_rtx;
      return;
    }

  /* Similarly, If (not *EXPR) implies (not cond), *EXPR must be true.  */
  if (rev && reve && implies_p (reve, rev))
    {
      *expr = const_true_rtx;
      return;
    }

  /* We would like to have some other tests here.  TODO.  */

  return;
}