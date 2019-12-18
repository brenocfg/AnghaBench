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
struct ivopts_data {int dummy; } ;
struct iv_use {int type; int /*<<< orphan*/  stmt; } ;
struct iv_cand {int dummy; } ;

/* Variables and functions */
#define  USE_ADDRESS 130 
#define  USE_COMPARE 129 
#define  USE_NONLINEAR_EXPR 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  mark_new_vars_to_rename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewrite_use_address (struct ivopts_data*,struct iv_use*,struct iv_cand*) ; 
 int /*<<< orphan*/  rewrite_use_compare (struct ivopts_data*,struct iv_use*,struct iv_cand*) ; 
 int /*<<< orphan*/  rewrite_use_nonlinear_expr (struct ivopts_data*,struct iv_use*,struct iv_cand*) ; 

__attribute__((used)) static void
rewrite_use (struct ivopts_data *data,
	     struct iv_use *use, struct iv_cand *cand)
{
  switch (use->type)
    {
      case USE_NONLINEAR_EXPR:
	rewrite_use_nonlinear_expr (data, use, cand);
	break;

      case USE_ADDRESS:
	rewrite_use_address (data, use, cand);
	break;

      case USE_COMPARE:
	rewrite_use_compare (data, use, cand);
	break;

      default:
	gcc_unreachable ();
    }
  mark_new_vars_to_rename (use->stmt);
}