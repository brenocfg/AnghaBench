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
struct hpsb_packet {int no_waiter; int /*<<< orphan*/  generation; } ;
struct hpsb_host {int /*<<< orphan*/  id; int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EXTPHYPACKET_TYPE_RESUME ; 
 int /*<<< orphan*/  HPSB_WARN (char*,int /*<<< orphan*/ ) ; 
 int NODEID_TO_NODE (int /*<<< orphan*/ ) ; 
 int PHYPACKET_PORT_SHIFT ; 
 int /*<<< orphan*/  get_hpsb_generation (struct hpsb_host*) ; 
 struct hpsb_packet* hpsb_make_phypacket (struct hpsb_host*,int) ; 
 int hpsb_send_packet (struct hpsb_packet*) ; 

__attribute__((used)) static int nodemgr_send_resume_packet(struct hpsb_host *host)
{
	struct hpsb_packet *packet;
	int error = -ENOMEM;

	packet = hpsb_make_phypacket(host,
			EXTPHYPACKET_TYPE_RESUME |
			NODEID_TO_NODE(host->node_id) << PHYPACKET_PORT_SHIFT);
	if (packet) {
		packet->no_waiter = 1;
		packet->generation = get_hpsb_generation(host);
		error = hpsb_send_packet(packet);
	}
	if (error)
		HPSB_WARN("fw-host%d: Failed to broadcast resume packet",
			  host->id);
	return error;
}