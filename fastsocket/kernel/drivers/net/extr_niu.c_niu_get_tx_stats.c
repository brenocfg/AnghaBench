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
struct tx_ring_info {scalar_t__ tx_errors; scalar_t__ tx_bytes; scalar_t__ tx_packets; } ;
struct niu {int num_tx_rings; TYPE_2__* dev; int /*<<< orphan*/  tx_rings; } ;
struct TYPE_3__ {unsigned long tx_packets; unsigned long tx_bytes; unsigned long tx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 struct tx_ring_info* ACCESS_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_get_tx_stats(struct niu *np)
{
	unsigned long pkts, errors, bytes;
	struct tx_ring_info *tx_rings;
	int i;

	pkts = errors = bytes = 0;

	tx_rings = ACCESS_ONCE(np->tx_rings);
	if (!tx_rings)
		goto no_rings;

	for (i = 0; i < np->num_tx_rings; i++) {
		struct tx_ring_info *rp = &tx_rings[i];

		pkts += rp->tx_packets;
		bytes += rp->tx_bytes;
		errors += rp->tx_errors;
	}

no_rings:
	np->dev->stats.tx_packets = pkts;
	np->dev->stats.tx_bytes = bytes;
	np->dev->stats.tx_errors = errors;
}