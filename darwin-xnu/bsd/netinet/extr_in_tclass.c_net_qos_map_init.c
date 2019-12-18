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
typedef  scalar_t__ errno_t ;
struct TYPE_2__ {int /*<<< orphan*/ * sotc_to_dscp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t SOTCIX_CTL ; 
 int /*<<< orphan*/  _DSCP_DF ; 
 int /*<<< orphan*/  _NET_SERVICE_TYPE_COUNT ; 
 int /*<<< orphan*/  default_dscp_to_wifi_ac_map ; 
 TYPE_1__ default_net_qos_dscp_map ; 
 int /*<<< orphan*/  fastlane_netsvctype_dscp_map ; 
 int /*<<< orphan*/  set_dscp_to_wifi_ac_map (int /*<<< orphan*/ ,int) ; 
 scalar_t__ set_netsvctype_dscp_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
net_qos_map_init()
{
	errno_t error;

	/*
	 * By default use the Fastlane DSCP mappngs
	 */
	error = set_netsvctype_dscp_map(_NET_SERVICE_TYPE_COUNT,
		fastlane_netsvctype_dscp_map);
	ASSERT(error == 0);

	/*
	 * No DSCP mapping for network control
	 */
	default_net_qos_dscp_map.sotc_to_dscp[SOTCIX_CTL] = _DSCP_DF;

	set_dscp_to_wifi_ac_map(default_dscp_to_wifi_ac_map, 1);
}