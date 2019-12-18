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
typedef  int /*<<< orphan*/  u64 ;
struct node_entry {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  host; } ;
struct hpsb_packet {int dummy; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 struct hpsb_packet* hpsb_make_writepacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  hpsb_node_fill_packet (struct node_entry*,struct hpsb_packet*) ; 
 scalar_t__ hpsb_send_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  hpsb_set_packet_complete_task (struct hpsb_packet*,int /*<<< orphan*/  (*) (struct hpsb_packet*),struct hpsb_packet*) ; 
 int /*<<< orphan*/  sbp2_free_packet (struct hpsb_packet*) ; 

__attribute__((used)) static int sbp2util_node_write_no_wait(struct node_entry *ne, u64 addr,
				       quadlet_t *buf, size_t len)
{
	struct hpsb_packet *packet;

	packet = hpsb_make_writepacket(ne->host, ne->nodeid, addr, buf, len);
	if (!packet)
		return -ENOMEM;

	hpsb_set_packet_complete_task(packet, sbp2_free_packet, packet);
	hpsb_node_fill_packet(ne, packet);
	if (hpsb_send_packet(packet) < 0) {
		sbp2_free_packet(packet);
		return -EIO;
	}
	return 0;
}