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
struct TYPE_2__ {int /*<<< orphan*/  pkt_free_list; } ;
struct pktcdvd_device {TYPE_1__ cdrw; } ;
struct packet_data {int /*<<< orphan*/  list; scalar_t__ cache_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_put_packet_data(struct pktcdvd_device *pd, struct packet_data *pkt)
{
	if (pkt->cache_valid) {
		list_add(&pkt->list, &pd->cdrw.pkt_free_list);
	} else {
		list_add_tail(&pkt->list, &pd->cdrw.pkt_free_list);
	}
}