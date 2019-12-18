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

/* Variables and functions */
 int /*<<< orphan*/  add_derived_ivs_candidates (struct ivopts_data*) ; 
 int /*<<< orphan*/  add_old_ivs_candidates (struct ivopts_data*) ; 
 int /*<<< orphan*/  add_standard_iv_candidates (struct ivopts_data*) ; 
 int /*<<< orphan*/  record_important_candidates (struct ivopts_data*) ; 

__attribute__((used)) static void
find_iv_candidates (struct ivopts_data *data)
{
  /* Add commonly used ivs.  */
  add_standard_iv_candidates (data);

  /* Add old induction variables.  */
  add_old_ivs_candidates (data);

  /* Add induction variables derived from uses.  */
  add_derived_ivs_candidates (data);

  /* Record the important candidates.  */
  record_important_candidates (data);
}