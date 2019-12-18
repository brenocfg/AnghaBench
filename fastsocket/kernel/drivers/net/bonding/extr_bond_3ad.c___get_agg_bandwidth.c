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
typedef  int u32 ;
struct aggregator {int num_of_ports; int /*<<< orphan*/  lag_ports; } ;

/* Variables and functions */
#define  AD_LINK_SPEED_BITMASK_10000MBPS 132 
#define  AD_LINK_SPEED_BITMASK_1000MBPS 131 
#define  AD_LINK_SPEED_BITMASK_100MBPS 130 
#define  AD_LINK_SPEED_BITMASK_10MBPS 129 
#define  AD_LINK_SPEED_BITMASK_1MBPS 128 
 int __get_link_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 __get_agg_bandwidth(struct aggregator *aggregator)
{
	u32 bandwidth=0;
	u32 basic_speed;

	if (aggregator->num_of_ports) {
		basic_speed = __get_link_speed(aggregator->lag_ports);
		switch (basic_speed) {
		case AD_LINK_SPEED_BITMASK_1MBPS:
			bandwidth = aggregator->num_of_ports;
			break;
		case AD_LINK_SPEED_BITMASK_10MBPS:
			bandwidth = aggregator->num_of_ports * 10;
			break;
		case AD_LINK_SPEED_BITMASK_100MBPS:
			bandwidth = aggregator->num_of_ports * 100;
			break;
		case AD_LINK_SPEED_BITMASK_1000MBPS:
			bandwidth = aggregator->num_of_ports * 1000;
			break;
		case AD_LINK_SPEED_BITMASK_10000MBPS:
			bandwidth = aggregator->num_of_ports * 10000;
			break;
		default:
			bandwidth=0; // to silent the compilor ....
		}
	}
	return bandwidth;
}