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
struct node_entry {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  generation; int /*<<< orphan*/  host; } ;
struct hpsb_packet {int /*<<< orphan*/  node_id; int /*<<< orphan*/  generation; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 

void hpsb_node_fill_packet(struct node_entry *ne, struct hpsb_packet *packet)
{
	packet->host = ne->host;
	packet->generation = ne->generation;
	smp_rmb();
	packet->node_id = ne->nodeid;
}