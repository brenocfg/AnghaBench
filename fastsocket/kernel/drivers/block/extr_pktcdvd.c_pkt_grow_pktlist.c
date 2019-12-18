#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pkt_free_list; } ;
struct TYPE_4__ {int size; } ;
struct pktcdvd_device {TYPE_1__ cdrw; TYPE_2__ settings; } ;
struct packet_data {int id; int /*<<< orphan*/  list; struct pktcdvd_device* pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct packet_data* pkt_alloc_packet_data (int) ; 
 int /*<<< orphan*/  pkt_shrink_pktlist (struct pktcdvd_device*) ; 

__attribute__((used)) static int pkt_grow_pktlist(struct pktcdvd_device *pd, int nr_packets)
{
	struct packet_data *pkt;

	BUG_ON(!list_empty(&pd->cdrw.pkt_free_list));

	while (nr_packets > 0) {
		pkt = pkt_alloc_packet_data(pd->settings.size >> 2);
		if (!pkt) {
			pkt_shrink_pktlist(pd);
			return 0;
		}
		pkt->id = nr_packets;
		pkt->pd = pd;
		list_add(&pkt->list, &pd->cdrw.pkt_free_list);
		nr_packets--;
	}
	return 1;
}