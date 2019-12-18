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
struct iv_use {int /*<<< orphan*/  stmt; } ;
struct iv_cand {int dummy; } ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int get_computation_cost_at (struct ivopts_data*,struct iv_use*,struct iv_cand*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
get_computation_cost (struct ivopts_data *data,
		      struct iv_use *use, struct iv_cand *cand,
		      bool address_p, bitmap *depends_on)
{
  return get_computation_cost_at (data,
				  use, cand, address_p, depends_on, use->stmt);
}