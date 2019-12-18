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
struct selfid {int phy_id; scalar_t__ port0; scalar_t__ port1; scalar_t__ port2; scalar_t__ contender; scalar_t__ link_active; int /*<<< orphan*/  extended; } ;
struct hpsb_host {int selfid_count; int irm_id; int node_count; scalar_t__ nodes_active; scalar_t__ topology_map; } ;
struct ext_selfid {int phy_id; int seq_nr; scalar_t__ porta; scalar_t__ portb; scalar_t__ portc; scalar_t__ portd; scalar_t__ porte; scalar_t__ portf; scalar_t__ portg; scalar_t__ porth; scalar_t__ extended; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_INFO (char*,...) ; 
 int LOCAL_BUS ; 
 scalar_t__ SELFID_PORT_PARENT ; 

__attribute__((used)) static int check_selfids(struct hpsb_host *host)
{
	int nodeid = -1;
	int rest_of_selfids = host->selfid_count;
	struct selfid *sid = (struct selfid *)host->topology_map;
	struct ext_selfid *esid;
	int esid_seq = 23;

	host->nodes_active = 0;

	while (rest_of_selfids--) {
		if (!sid->extended) {
			nodeid++;
			esid_seq = 0;

			if (sid->phy_id != nodeid) {
				HPSB_INFO("SelfIDs failed monotony check with "
					  "%d", sid->phy_id);
				return 0;
			}

			if (sid->link_active) {
				host->nodes_active++;
				if (sid->contender)
					host->irm_id = LOCAL_BUS | sid->phy_id;
			}
		} else {
			esid = (struct ext_selfid *)sid;

			if ((esid->phy_id != nodeid)
			    || (esid->seq_nr != esid_seq)) {
				HPSB_INFO("SelfIDs failed monotony check with "
					  "%d/%d", esid->phy_id, esid->seq_nr);
				return 0;
			}
			esid_seq++;
		}
		sid++;
	}

	esid = (struct ext_selfid *)(sid - 1);
	while (esid->extended) {
		if ((esid->porta == SELFID_PORT_PARENT) ||
		    (esid->portb == SELFID_PORT_PARENT) ||
		    (esid->portc == SELFID_PORT_PARENT) ||
		    (esid->portd == SELFID_PORT_PARENT) ||
		    (esid->porte == SELFID_PORT_PARENT) ||
		    (esid->portf == SELFID_PORT_PARENT) ||
		    (esid->portg == SELFID_PORT_PARENT) ||
		    (esid->porth == SELFID_PORT_PARENT)) {
			HPSB_INFO("SelfIDs failed root check on "
				  "extended SelfID");
			return 0;
		}
		esid--;
	}

	sid = (struct selfid *)esid;
	if ((sid->port0 == SELFID_PORT_PARENT) ||
	    (sid->port1 == SELFID_PORT_PARENT) ||
	    (sid->port2 == SELFID_PORT_PARENT)) {
		HPSB_INFO("SelfIDs failed root check");
		return 0;
	}

	host->node_count = nodeid + 1;
	return 1;
}