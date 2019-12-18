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
struct hpsb_host {int /*<<< orphan*/  node_id; int /*<<< orphan*/  selfid_count; int /*<<< orphan*/ * topology_map; scalar_t__ in_bus_reset; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_NOTICE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPSB_VERBOSE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODEID_TO_BUS (int /*<<< orphan*/ ) ; 

void hpsb_selfid_received(struct hpsb_host *host, quadlet_t sid)
{
	if (host->in_bus_reset) {
		HPSB_VERBOSE("Including SelfID 0x%x", sid);
		host->topology_map[host->selfid_count++] = sid;
	} else {
		HPSB_NOTICE("Spurious SelfID packet (0x%08x) received from bus %d",
			    sid, NODEID_TO_BUS(host->node_id));
	}
}