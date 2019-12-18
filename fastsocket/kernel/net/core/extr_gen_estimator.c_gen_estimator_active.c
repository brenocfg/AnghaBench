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
struct gnet_stats_rate_est {int dummy; } ;
struct gnet_stats_basic_packed {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/ * gen_find_node (struct gnet_stats_basic_packed const*,struct gnet_stats_rate_est const*) ; 

bool gen_estimator_active(const struct gnet_stats_basic_packed *bstats,
			  const struct gnet_stats_rate_est *rate_est)
{
	ASSERT_RTNL();

	return gen_find_node(bstats, rate_est) != NULL;
}