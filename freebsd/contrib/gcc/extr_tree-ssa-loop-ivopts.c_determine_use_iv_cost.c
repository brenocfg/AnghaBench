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
struct iv_use {int type; } ;
struct iv_cand {int dummy; } ;

/* Variables and functions */
#define  USE_ADDRESS 130 
#define  USE_COMPARE 129 
#define  USE_NONLINEAR_EXPR 128 
 int determine_use_iv_cost_address (struct ivopts_data*,struct iv_use*,struct iv_cand*) ; 
 int determine_use_iv_cost_condition (struct ivopts_data*,struct iv_use*,struct iv_cand*) ; 
 int determine_use_iv_cost_generic (struct ivopts_data*,struct iv_use*,struct iv_cand*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static bool
determine_use_iv_cost (struct ivopts_data *data,
		       struct iv_use *use, struct iv_cand *cand)
{
  switch (use->type)
    {
    case USE_NONLINEAR_EXPR:
      return determine_use_iv_cost_generic (data, use, cand);

    case USE_ADDRESS:
      return determine_use_iv_cost_address (data, use, cand);

    case USE_COMPARE:
      return determine_use_iv_cost_condition (data, use, cand);

    default:
      gcc_unreachable ();
    }
}