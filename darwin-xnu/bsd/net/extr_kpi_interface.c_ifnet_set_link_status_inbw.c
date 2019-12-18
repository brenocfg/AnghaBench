#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ eff_bw; scalar_t__ max_bw; } ;
struct ifnet {TYPE_5__ if_input_bw; TYPE_4__* if_link_status; } ;
struct if_wifi_status_v1 {scalar_t__ dl_effective_bandwidth; scalar_t__ dl_max_bandwidth; int /*<<< orphan*/  valid_bitmask; } ;
struct TYPE_6__ {struct if_wifi_status_v1 if_status_v1; } ;
struct TYPE_7__ {TYPE_1__ if_wifi_u; } ;
struct TYPE_8__ {TYPE_2__ ifsr_wifi; } ;
struct TYPE_9__ {TYPE_3__ ifsr_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_WIFI_DL_EFFECTIVE_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  IF_WIFI_DL_MAX_BANDWIDTH_VALID ; 

__attribute__((used)) static void
ifnet_set_link_status_inbw(struct ifnet *ifp)
{
	struct if_wifi_status_v1 *sr;

	sr = &ifp->if_link_status->ifsr_u.ifsr_wifi.if_wifi_u.if_status_v1;
	if (ifp->if_input_bw.eff_bw != 0) {
		sr->valid_bitmask |=
		    IF_WIFI_DL_EFFECTIVE_BANDWIDTH_VALID;
		sr->dl_effective_bandwidth =
		    ifp->if_input_bw.eff_bw;
	}
	if (ifp->if_input_bw.max_bw != 0) {
		sr->valid_bitmask |=
		    IF_WIFI_DL_MAX_BANDWIDTH_VALID;
		sr->dl_max_bandwidth = ifp->if_input_bw.max_bw;
	}
}