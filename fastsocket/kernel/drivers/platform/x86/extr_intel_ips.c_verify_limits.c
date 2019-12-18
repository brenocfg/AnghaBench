#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ips_driver {int mcp_power_limit; int mcp_temp_limit; TYPE_1__* limits; } ;
struct TYPE_2__ {int mcp_power_limit; int core_temp_limit; int mch_temp_limit; } ;

/* Variables and functions */
 int min (int,int) ; 

__attribute__((used)) static void verify_limits(struct ips_driver *ips)
{
	if (ips->mcp_power_limit < ips->limits->mcp_power_limit ||
	    ips->mcp_power_limit > 35000)
		ips->mcp_power_limit = ips->limits->mcp_power_limit;

	if (ips->mcp_temp_limit < ips->limits->core_temp_limit ||
	    ips->mcp_temp_limit < ips->limits->mch_temp_limit ||
	    ips->mcp_temp_limit > 150)
		ips->mcp_temp_limit = min(ips->limits->core_temp_limit,
					  ips->limits->mch_temp_limit);
}