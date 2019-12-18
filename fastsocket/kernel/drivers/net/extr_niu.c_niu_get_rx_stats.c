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
struct rx_ring_info {scalar_t__ rx_errors; scalar_t__ rx_dropped; scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;
struct niu {int num_rx_rings; TYPE_2__* dev; int /*<<< orphan*/  rx_rings; } ;
struct TYPE_3__ {unsigned long rx_packets; unsigned long rx_bytes; unsigned long rx_dropped; unsigned long rx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 struct rx_ring_info* ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_sync_rx_discard_stats (struct niu*,struct rx_ring_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_get_rx_stats(struct niu *np)
{
	unsigned long pkts, dropped, errors, bytes;
	struct rx_ring_info *rx_rings;
	int i;

	pkts = dropped = errors = bytes = 0;

	rx_rings = ACCESS_ONCE(np->rx_rings);
	if (!rx_rings)
		goto no_rings;

	for (i = 0; i < np->num_rx_rings; i++) {
		struct rx_ring_info *rp = &rx_rings[i];

		niu_sync_rx_discard_stats(np, rp, 0);

		pkts += rp->rx_packets;
		bytes += rp->rx_bytes;
		dropped += rp->rx_dropped;
		errors += rp->rx_errors;
	}

no_rings:
	np->dev->stats.rx_packets = pkts;
	np->dev->stats.rx_bytes = bytes;
	np->dev->stats.rx_dropped = dropped;
	np->dev->stats.rx_errors = errors;
}